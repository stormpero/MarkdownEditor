#include "mainwindow.h"
#include "ui_mainwindow.h"

int MainWindow::SaveDialog()
{
    if(isChanged)
    {
        int k = QMessageBox::warning(this, tr("Markdown Editor"),
                                     tr("Документ был изменён\n"
                                        "Вы хотите сохранить свои изменения?"),
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);

        if (k == QMessageBox::Save)
            SaveFile();

        else if (k == QMessageBox::Cancel)
            return -1;
    }
    return 0;
}

void MainWindow::disableMenu(bool a)
{
    ui->action_save->setDisabled(a);
    ui->action_saveAs->setDisabled(a);
    ui->action_toHTML->setDisabled(a);
    ui->action_toPDF->setDisabled(a);
    ui->action_img->setDisabled(a);
    ui->action_link->setDisabled(a);
}



