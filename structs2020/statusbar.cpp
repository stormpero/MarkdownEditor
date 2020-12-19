#include "mainwindow.h"

void MainWindow::CreateStatusBar()
{
    cursorPosition = new QLabel;
    fileSize = new QLabel;
    statusBar()->addWidget(fileSize);
    statusBar()->addWidget(cursorPosition);
    cursorPosition->hide();
    fileSize->hide();
    statusBar()->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
}
