#include "mainwindow.h"

int MainWindow::DialogSaveWindow()
{
    int ret = QMessageBox::warning(this, tr("Markdown Editor"),
                                   tr("Документ был изменён\n"
                                      "Вы хотите сохранить свои изменения?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
    return ret;
}


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
