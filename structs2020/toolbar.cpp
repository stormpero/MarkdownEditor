#include "mainwindow.h"

QToolBar* MainWindow::createMainToolBar()
{
    QToolBar* bar = new QToolBar("Main ToolBar");
    bar->addAction(QPixmap(":/img/Toolbar/newfile.ico"), "Создать файл", this, SLOT(CreateNewFile()));
    bar->addAction(QPixmap(":/img/Toolbar/openfile.ico"), "Открыть файл", this, SLOT(OpenFile()));
    bar->setMovable(false);
    bar->setIconSize(QSize(35,35));

    return bar;
}
QToolBar* MainWindow::createWorkToolBar()
{
    QToolBar* bar = new QToolBar("Work ToolBar");
    bar->addAction(QPixmap(":/img/Toolbar/save.ico"), "Сохранить", this, SLOT(SaveFile()));
    bar->addAction(QPixmap(":/img/Toolbar/saveas.ico"), "Сохранить как", this, SLOT(SaveFileAs()));
    bar->addSeparator();
    bar->addAction(QPixmap(":/img/Toolbar/image.ico"), "Вставить изображение");
    bar->addAction(QPixmap(":/img/Toolbar/link.ico"), "Вставить ссылку");
    bar->addSeparator();
    bar->addAction(QPixmap(":/img/Toolbar/tohtml.ico"), "Экспорт в html");
    bar->addAction(QPixmap(":/img/Toolbar/topdf.ico"), "Экспорт в pdf");
    bar->setMovable(false);
    bar->setIconSize(QSize(35,35));
    return bar;
}
QToolBar* MainWindow::createExtraToolBar()
{
    QToolBar* bar = new QToolBar("Extra ToolBar");
    html_ico = bar->addAction(QPixmap(":/img/Toolbar/extra_html.ico"), "Предпросмотр Html", this, SLOT(HtmlCheck()));
    text_ico = bar->addAction(QPixmap(":/img/Toolbar/extra_txt.ico"), "Предпросмотр", this, SLOT(PreviewCheck()));
    markdown_ico = bar->addAction(QPixmap(":/img/Toolbar/extra_markdown.ico"), "Редактор Markdown", this, SLOT(MarkdowneditCheck()));

    markdown_ico->setDisabled(true);
    html_ico->setDisabled(true);
    text_ico->setDisabled(true);

    markdown_ico->setCheckable(true);
    html_ico->setCheckable(true);
    text_ico->setCheckable(true);

    bar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
    bar->setMovable(false);
    bar->setIconSize(QSize(35,35));

    return bar;
}

void MainWindow::MarkdowneditCheck()
{
    MarkdowntextEdit->hide();
    if (markdown_ico->isChecked())
    {
        MarkdowntextEdit->show();
    }

}
void MainWindow::PreviewCheck()
{
    TextPreview->hide();
    if (text_ico->isChecked())
    {
        TextPreview->show();
    }
}
void MainWindow::HtmlCheck()
{
    htmlPreview->hide();
    if (html_ico->isChecked())
    {
        htmlPreview->show();
    }
}

void MainWindow::CreateNewFile()
{
    if (isExistButNoWay)
        return;

    if (checkForChanges() == -1)
        return;

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    markdown_ico->setChecked(true);
    MarkdowntextEdit->clear();
    MarkdowntextEdit->show();
    setWindowTitle(QString("new - Markdown Editor"));
    isChanged = false;
    isExistButNoWay = true;

}

void MainWindow::OpenFile()
{
    checkForChanges();
    QString fileName = QFileDialog::getOpenFileName(0, "Открыть файл", "", "*.markdown");
    if(fileName.isEmpty())
    {
        qDebug() << "Read and write paths are empty";
        return;
    }
    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "Error while opening for writing and reading";
        return;
    }

    MarkdowntextEdit->setPlainText(file.readAll());

    file.close();
    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    markdown_ico->setChecked(true);
    MarkdowntextEdit->show();
    isChanged = false;
    setWindowTitle(QString(fileName + " - Markdown Editor"));
}

void MainWindow::SaveFile()
{
    if(!isChanged)
        return;
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "1";
        SaveFileAs();
        return;
    }
    file.write(MarkdowntextEdit->toPlainText().toStdString().data());
    file.close();
}

int MainWindow::SaveFileAs() // 1 - saveas | 0 - no save | -1 - cancel
{
    QString fileName = QFileDialog::getSaveFileName(0, "Сохранить файл как","", "*.markdown");
    if(fileName.isEmpty())
    {
        qDebug() << "Write path is empty";
        return -1;
    }
    file.setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error while opening for writing";
        return -1;
    }
    file.write(MarkdowntextEdit->toPlainText().toStdString().data());
    file.close();
    return 1;
}

int MainWindow::DialogSaveWindow()
{
    int ret = QMessageBox::warning(this, tr("Markdown Editor"),
                                   tr("Документ был изменён\n"
                                      "Вы хотите сохранить свои изменения?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
    return ret;
}






