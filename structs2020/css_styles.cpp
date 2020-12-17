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


//    QString verticalScroll("QScrollBar:vertical {"
//                           "    border: 0px solid #c6c6c6;"
//                           "    background: transparent;"
//                           "    width: 13px;    "
//                           "    margin: 0px 0px 0px 0px;"
//                           "}"
//                           "QScrollBar::handle {"
//                           "    background: #c6c6c6;"
//                           "    border: 2px solid gray;"
//                           "    border-radius: 6px;"
//                           "}"
//                           "QScrollBar::add-line:vertical {"
//                           "    height: 0px;"
//                           "    subcontrol-position: bottom;"
//                           "    subcontrol-origin: margin;"
//                           "}"
//                           "QScrollBar::sub-line:vertical {"
//                           "    height: 0 px;"
//                           "    subcontrol-position: top;"
//                           "    subcontrol-origin: margin;"
//                           "}");

//    QString backgroundStyle(
//                            "border-radius:10px;"
//                             "border: 2px solid #c6c6c6"

//                            );
//

//    //WorkToolBar->setStyleSheet("background-color: #C9D6DF");

//    MarkdowntextEdit->setStyleSheet(verticalScroll);
//    Preview->setStyleSheet(verticalScroll);
//    htmlPreview->setStyleSheet(verticalScroll);

//    htmlPreview->setStyleSheet(backgroundStyle);
//    Preview->setStyleSheet(backgroundStyle);
}
