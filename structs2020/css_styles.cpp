#include "mainwindow.h"

void MainWindow::initializationCSS()
{
    QString verticalScroll("QScrollBar:vertical {"
                           "    border: 0px solid #c6c6c6;"
                           "    background: transparent;"
                           "    width: 13px;    "
                           "    margin: 0px 0px 0px 0px;"
                           "}"
                           "QScrollBar::handle {"
                           "    background: #c6c6c6;"
                           "    border: 2px solid gray;"
                           "    border-radius: 6px;"
                           "}"
                           "QScrollBar::add-line:vertical {"
                           "    height: 0px;"
                           "    subcontrol-position: bottom;"
                           "    subcontrol-origin: margin;"
                           "}"
                           "QScrollBar::sub-line:vertical {"
                           "    height: 0 px;"
                           "    subcontrol-position: top;"
                           "    subcontrol-origin: margin;"
                           "}");

    MarkdowntextEdit->setStyleSheet(verticalScroll);
    TextPreview->setStyleSheet(verticalScroll);
    //htmlPreview->setStyleSheet(verticalScroll);
}
