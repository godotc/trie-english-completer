#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qabstractitemmodel.h"
#include "qcompleter.h"
#include <QAbstractItemModel>
#include <QMainWindow>

#include "TextEditor.h"


namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void about();

  private:
    QAbstractItemModel *modelFromFile(const QString &fileName);
    QAbstractItemModel *modelFromTrieTree(const QString &prefix) { return nullptr; }

    void createMenu();

  private:
    // Ui::MainWindow *ui;

    QCompleter *completer = nullptr;
    TextEditor *textEditor;
};

#endif // MAINWINDOW_H
