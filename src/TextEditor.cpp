#include "TextEditor.h"

#include "qabstractitemmodel.h"
#include "qabstractitemview.h"
#include "qchar.h"
#include "qcolor.h"
#include "qcompleter.h"
#include "qcoreevent.h"
#include "qevent.h"
#include "qframe.h"
#include "qglobal.h"
#include "qlistview.h"
#include "qnamespace.h"
#include "qpalette.h"
#include "qscrollbar.h"
#include "qsize.h"
#include "qstringliteral.h"
#include "qtextcursor.h"
#include "qtreewidget.h"
#include <qdebug.h>
#include <qheaderview.h>
#include <qrect.h>
#include <qstringlistmodel.h>

TextEditor::TextEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    word_list = new QTreeWidget();
    word_list->setWindowFlags(Qt::Popup);
    word_list->setFocusPolicy(Qt::NoFocus);
    word_list->setMouseTracking(true);
    word_list->setColumnCount(1);
    word_list->setUniformRowHeights(true);
    word_list->setRootIsDecorated(false);
    word_list->setSelectionBehavior(QTreeWidget::SelectRows);
    word_list->setFrameStyle(QFrame::Box | QFrame::Plain);
    word_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    word_list->header()->hide();

    word_list->installEventFilter(this);


    connect(this, &QPlainTextEdit::textChanged, this, &TextEditor::onTextChanged);

    connect(word_list, &QTreeWidget::itemClicked, this, &TextEditor::doneCompletion);
}

TextEditor::~TextEditor()
{
    delete word_list;
    qDebug() << "~TextEditor";
}


bool TextEditor::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj != word_list)
        return false;


    if (ev->type() == QEvent::MouseButtonPress) {
        word_list->hide();
        this->setFocus();
        return true;
    }

    auto c = textCursor();

    if (ev->type() == QEvent::KeyPress) {
        bool consumed = false;

        int key = static_cast<QKeyEvent *>(ev)->key();

        switch (key) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
            doneCompletion();
            consumed = true;
            break;

        // case Qt::Key_Space:
        //     c.insertText(" ");
        case Qt::Key_Escape:
            this->setFocus();
            word_list->hide();
            consumed = true;
            break;

        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;

        default:
            this->setFocus();
            this->event(ev);
            word_list->hide();
            break;
        }

        return consumed;
    }

    return false;
}


void TextEditor::showSuggestion(const QVector<QString> &choices)
{
    if (choices.isEmpty())
        return;

    const QPalette &palette = this->palette();
    QColor          color   = palette.color(QPalette::Disabled, QPalette::WindowText);

    // word_list->setUpdatesEnabled(false);
    word_list->clear();

    for (const auto &word : choices)
    {
        auto item = new QTreeWidgetItem(word_list);
        item->setText(0, word);
        item->setForeground(0, color);
    }
    word_list->setCurrentItem(word_list->topLevelItem(0));
    word_list->resizeColumnToContents(0);

    // word_list->setUpdatesEnabled(true);

    auto cr = cursorRect();
    word_list->move(this->mapToGlobal(cr.bottomLeft()));

    // word_list->setFocus();

    word_list->show();
    this->setFocus();
}

void TextEditor::doneCompletion()
{
    word_list->hide();
    this->setFocus();
    QTreeWidgetItem *item = word_list->currentItem();

    if (item) {
        auto word = item->text(0);

        auto c = textCursor();

        c.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
        c.removeSelectedText();
        c.insertText(word);
    }
}

void TextEditor::onTextChanged()
{
    word_list->hide();

    auto cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);

    if (cursor.atEnd()) {
        return;
    }

    QString prefix = cursor.selectedText().trimmed();
    qDebug() << "Prefix = " << prefix;

    if (prefix.isEmpty() || !prefix.back().isLetter()) {
        return;
    }

    QVector<QString> successors;

    successors << "hello"
               << "world";

    if (!successors.empty()) {
        showSuggestion(successors);
    }
}
