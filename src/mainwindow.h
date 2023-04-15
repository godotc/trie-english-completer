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
    // Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

  private slots:
    void about();

  private:
    void createMenu();

  private:

    TextEditor *textEditor;
};

#endif // MAINWINDOW_H
