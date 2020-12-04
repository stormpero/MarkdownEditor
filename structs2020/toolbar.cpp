#include "mainwindow.h"

QToolBar* MainWindow::createMainToolBar()
{
    QToolBar* bar = new QToolBar("Main ToolBar");
    bar->addAction(QPixmap(":/img/Toolbar/newfile.ico"), "Создать файл", this, SLOT(CreateNewFile()));
    bar->addAction(QPixmap(":/img/Toolbar/openfile.ico"), "Открыть файл", this, SLOT(OpenFile()));
    bar->setMovable(false);
    bar->setIconSize(QSize(25,25));

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
    if (isExistButNoWay)
        return;

    if (SaveDialog() == -1)
        return;

    setWindowTitle(QString("*%1 - Markdown Editor").arg("new"));

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
    if (SaveDialog() == -1)
        return;
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

    setWindowTitle(QString("*%1 - Markdown Editor").arg(file.fileName()));

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    markdown_ico->setChecked(true);
    MarkdowntextEdit->show();
    isChanged = false;
    isExistButNoWay = false;
    statusBar()->showMessage(QString::number(file.size()));
}

void MainWindow::SaveFile()
{
    if(!isChanged)
        return;

    if (!file.exists())
    {
        SaveFileAs();
        return;
    }
    if (!file.isOpen())
        file.open(QIODevice::WriteOnly);

    file.write(MarkdowntextEdit->toPlainText().toStdString().data());
    setWindowTitle(QString(windowTitle().remove(0,1)));
    file.close();
    isChanged = false;
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






