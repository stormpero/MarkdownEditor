#include "mainwindow.h"

int MainWindow::checkForChanges()
{
    if(isChanged)
    {
        int k = DialogSaveWindow();

        if (k == QMessageBox::Save)
            SaveFile();

        else if (k == QMessageBox::Cancel)
            return -1;
    }
    return 0;
}
