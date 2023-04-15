#pragma once

#include <QApplication>
#include <QCompleter>
#include <QTextEdit>
#include <qobject.h>

class TextEditor : public QTextEdit
{
    // Q_OBJECT

  public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

    void                      SetCompleter(QCompleter *c);
    [[nodiscard]] QCompleter *Completer() const;

  protected:
    void keyPressEvent(QKeyEvent *e) override;
    void focusInEvent(QFocusEvent *e) override;

  private slots:
    void insertCompletion(const QString &completion);

  private:
    [[nodiscard]] QString textUnderCursor() const;

  private:
    QCompleter *c = nullptr;
};
