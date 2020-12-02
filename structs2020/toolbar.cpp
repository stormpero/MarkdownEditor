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
    bar->setIconSize(QSize(25,25));
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
    bar->setIconSize(QSize(25,25));

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
    checkForChanges();
    QString fileName = QFileDialog::getSaveFileName(0, "Создать файл", "*.markdown");
    if(fileName.isEmpty())
    {
        qDebug() << "Write path is empty";
        return;
    }
    file.setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error while opening for writing";
        return;
    }
    while (!file.atEnd())
    {
         QByteArray line = file.readLine();
         MarkdowntextEdit->appendPlainText(line);
    }

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    markdown_ico->setChecked(true);
    MarkdowntextEdit->show();
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

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    markdown_ico->setChecked(true);
    MarkdowntextEdit->show();
}

void MainWindow::SaveFile()
{
    if(!isChanged)
        return;

    QTextStream out(&file);
    out << MarkdowntextEdit->document()->toRawText().toStdString().data();
    out << "\0";
}

int MainWindow::SaveFileAs()
{

return 1;
}
