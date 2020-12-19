#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::initializationCSS()
{
    QFile file(":/styles.css");
    file.open(QFile::ReadOnly);


    QString styles(file.readAll());

    MarkdowntextEdit->setStyleSheet(styles);
    Preview->setStyleSheet(styles);
    htmlPreview->setStyleSheet(styles);
    menuBar()->setStyleSheet(styles);
    statusBar()->setStyleSheet(styles);
    centralWidget()->setStyleSheet("background-color: #DFD3D3");
    this->WorkToolBar->setStyleSheet(styles);
}
