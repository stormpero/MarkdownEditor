#include "mainwindow.h"

void MainWindow::initializationCSS()
{
    QString verticalScroll("QPlainTextEdit{"
                           "border-radius:10px;"
                           "border: 2px solid #c6c6c6"
                           "}"
                           "QScrollBar:vertical {"
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

    QString backgroundStyle(
                            "border-radius:10px;"
                             "border: 2px solid #c6c6c6"

                            );
    centralWidget()->setStyleSheet("background-color: #F0F5F9");

    //WorkToolBar->setStyleSheet("background-color: #C9D6DF");

    MarkdowntextEdit->setStyleSheet(verticalScroll + backgroundStyle);
    Preview->setStyleSheet(verticalScroll);
    htmlPreview->setStyleSheet(verticalScroll);

    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    MarkdowntextEdit->setFont(font);

    htmlPreview->setStyleSheet(backgroundStyle);
    Preview->setStyleSheet(backgroundStyle);
}
