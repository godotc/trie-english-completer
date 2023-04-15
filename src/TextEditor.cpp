#include "TextEditor.h"
#include "qabstractitemview.h"
#include "qcompleter.h"
#include "qglobal.h"
#include "qnamespace.h"
#include "qwidget.h"
#include <QKeyEvent>
#include <qscrollbar.h>

TextEditor::TextEditor(QWidget *parent)
    : QTextEdit(parent)
{
    setPlainText(tr("This TextEdit provides autocompletions for words that have more than"
                    " 3 characters. You can trigger autocompletion using ") +
                 QKeySequence("Ctrl+E").toString(QKeySequence::NativeText));
}

TextEditor::~TextEditor() {}


void TextEditor::SetCompleter(QCompleter *completer)
{
    if (c)
        c->disconnect(this);

    c = completer;

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);

    connect(c, QOverload<const QString &>::of(&QCompleter::activated), this, &TextEditor::insertCompletion);
}


QCompleter *TextEditor::Completer() const { return c; }

void TextEditor::insertCompletion(const QString &completion)
{
    if (c->widget() != this)
        return;

    QTextCursor tc = textCursor();

    int extra = completion.length() - c->completionPrefix().length();

    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString TextEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void TextEditor::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QTextEdit::focusInEvent(e);
}


void TextEditor::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible())
    {
        switch (e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }


    // I want always do complete
    const bool isShortcut = (e->modifiers().testFlag(Qt::ControlModifier) && e->key() == Qt::Key_P); // CTRL+P

    const bool ctrlOrShift = e->modifiers().testFlag(Qt::ControlModifier) ||
                             e->modifiers().testFlag(Qt::ShiftModifier);
    if (!c || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    const bool     hasModifier      = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString        completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty() || completionPrefix.length() < 3 || eow.contains(e->text().right(1)))) {
        c->popup()->hide();
        return;
    }

    if (completionPrefix != c->completionPrefix()) {
        c->setCompletionPrefix(completionPrefix);
        c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(c->popup()->sizeHintForColumn(0) + c->popup()->verticalScrollBar()->sizeHint().width());
    c->complete(cr); // popup it up!
}
