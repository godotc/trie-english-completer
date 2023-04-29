#pragma once

#include <pack.h>

#include "qabstractitemview.h"
#include "qcoreevent.h"
#include "qlistview.h"
#include "qobject.h"
#include "qvector.h"
#include <QApplication>
#include <QCompleter>
#include <QObject>
#include <QTreeWidget>
#include <memory>
#include <qplaintextedit.h>



class TextEditor : public QPlainTextEdit
{

  public:
    TextEditor(QWidget *parent = nullptr);
    ~TextEditor();

  public:
    bool eventFilter(QObject *obj, QEvent *ev) override;
    void showSuggestion(const QVector<QString> &choices);

  public:
    QVector<QString> GetSuggestions(QString &prefix);
    void             InitTrie();


  private slots:

    void onTextChanged();
    void doneCompletion();

  private:
    QTreeWidget                    *word_list;
    std::unique_ptr<trie::PackTrie> trie;
};
