#pragma once

#include "qabstractitemview.h"
#include "qcoreevent.h"
#include "qlistview.h"
#include "qobject.h"
#include "qvector.h"
#include <QApplication>
#include <QCompleter>
#include <QObject>
#include <QTreeWidget>
#include <qplaintextedit.h>



class TextEditor : public QPlainTextEdit
{

  public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

  public:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void showSuggestion(const QVector<QString> &choices);

  private slots:

    void onTextChanged();
    void doneCompletion();

  private:
    QTreeWidget *word_list;
};
