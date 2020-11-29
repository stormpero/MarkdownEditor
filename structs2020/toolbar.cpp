#include "mainwindow.h"
#include <QToolBar>

QToolBar* MainWindow::createMainToolBar()
{
    QToolBar* bar = new QToolBar("Main ToolBar");
    bar->addAction(QPixmap(":/img/Toolbar/newfile.ico"), "Создать файл", this, SLOT(CreateNewFile()));
    bar->addAction(QPixmap(":/img/Toolbar/openfile.ico"), "Открыть файл", this, SLOT(OpenFile()));
    bar->addSeparator();
    bar->setMovable(false);
    bar->setIconSize(QSize(35,35));

    return bar;
}
QToolBar* MainWindow::createWorkToolBar()
{
    QToolBar* bar = new QToolBar("Work ToolBar");
    bar->addAction(QPixmap(":/img/Toolbar/save.ico"), "Сохранить");
    bar->addAction(QPixmap(":/img/Toolbar/saveas.ico"), "Сохранить как");
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

void MainWindow::OpenFile()
{
    WorkToolBar->setDisabled(false);
}

void MainWindow::CreateNewFile()
{
    WorkToolBar->setDisabled(false);
}
