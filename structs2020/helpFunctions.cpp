#include "mainwindow.h"
#include "ui_mainwindow.h"

#define KB 1024
#define MB 1048576

int MainWindow::SaveDialog()
{

    int k = QMessageBox::warning(this, tr("Markdown Editor"),
                                 tr("Документ был изменён\n"
                                    "Вы хотите сохранить свои изменения?"),
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);

    if (k == QMessageBox::Save)
    {
        SaveFile();
    }
    else if (k == QMessageBox::Cancel)
        return -1;

    file.close();
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

void MainWindow::updateFileSize()
{
    int fileSize = MarkdowntextEdit->toPlainText().size();
    QString unit = "Б";
    if (fileSize > KB)
    {
        fileSize /= KB;
        unit = "КБ";
    }
    else if (fileSize > MB)
    {
        fileSize /= MB;
        unit = "МБ";
    }
   MainWindow::fileSize->setText(QString("Размер файла: %1 %2").arg(fileSize).arg(unit));
}

