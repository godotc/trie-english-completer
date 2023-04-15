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


    this->textEditor = new TextEditor;

    completer = new QCompleter(this);
    completer->setModel(modelFromFile(":/res/english-words.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);

    this->textEditor->SetCompleter(completer);


    setCentralWidget(textEditor);
    resize(800, 600);
    setWindowTitle("Editor");
}

MainWindow::~MainWindow()
{
    // delete ui;
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


auto MainWindow::modelFromFile(const QString &fileName) -> QAbstractItemModel *
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CUROR
    QGuiApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif

    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty()) {
            words << QString::fromUtf8(line.trimmed());
        }
    }

#ifndef QT_NO_CUROR
    QGuiApplication::restoreOverrideCursor();
#endif

    return new QStringListModel(words, completer);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates the "
                                             "different features of the QCompleter class."));
}

/*
    void MainWindow::onTextChanged()
    {
        textEdit->setFocus();
        wordList->show();

        QTextCursor cursor = textEdit->textCursor();
        cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);

        if (cursor.atEnd()) {
            qDebug() << "cursor is not within a word currently, hide";
            wordList->hide();
            return;
        }

        QString prefix = cursor.selectedText().trimmed();
        qDebug() << "Prefix = " << prefix;

        if (prefix.isEmpty()) {
            qDebug() << "prefix is empty , hide";
            wordList->hide();
            return;
        }
        if (!prefix.back().isLetter()) {
            qDebug() << "previous one character not word, hide";
            wordList->hide();
            return;
        }
        // If the last character of the prefix is a space, hide the list widget
        if (prefix.back() == ' ') {
            qDebug() << "previous one character is space ' ', hide";
            wordList->hide();
            return;
        }


        QStringList successors = QStringList({"hello", "world"});

        if (!successors.isEmpty()) {
            qDebug() << "successors not empty";

            wordList->clear();
            wordList->addItems(successors);

            // prompt pannel position change
            QRect  cursorRect = textEdit->cursorRect(cursor);
            QPoint popupPos   = cursorRect.bottomLeft();
            popupPos.setY(popupPos.y() + 2);
            wordList->move(textEdit->mapToGlobal(popupPos));

            wordList->showPopup();
        }
        else {
            wordList->hide();
            return;
        }
    }

    void MainWindow::onSuccessorClicked(int index)
    {
        auto *wordList  = qobject_cast<QComboBox *>(sender());
        auto  successor = wordList->itemText(index);
        auto  cursor    = textEdit->textCursor();

        // replace prefix with complete word
        cursor.movePosition(QTextCursor::StartOfWord, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        cursor.insertText(successor);

        wordList->hide();
        textEdit->setFocus();
    }

    void MainWindow::onWordListHighlighted(const QString &text)
    {
        Q_UNUSED(text);
        textEdit->setFocus();
    }
*/
