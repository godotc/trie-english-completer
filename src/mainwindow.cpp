#include "mainwindow.h"
// #include "ui_mainwindow.h"

#include <TrieTree.h>

#include "TextEditor.h"
#include "qabstractitemmodel.h"
#include "qcompleter.h"
#include "qcursor.h"
#include "qguiapplication.h"
#include "qnamespace.h"
#include <QMenuBar>
#include <qaction.h>
#include <qdebug.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qstringlistmodel.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
//,ui(new Ui::MainWindow)
{
    //   ui->setupUi(this);

    createMenu();


    this->textEditor = new TextEditor(this);

    setCentralWidget(textEditor);
    resize(800, 600);
    setWindowTitle("Editor");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenu()
{
    auto *exitAction = new QAction(tr("Exit"), this);
    auto *aboutAct   = new QAction(tr("About"), this);
    auto *aboutQtAct = new QAction(tr("About Qt"), this);

    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("About"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("Author: @godot42"
                                             "Email: disyourself@qq.com"));
}
