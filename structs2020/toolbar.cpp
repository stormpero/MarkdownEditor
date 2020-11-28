#include "mainwindow.h"
#include <QToolBar>

QToolBar* MainWindow::createMainToolBar()
{
    QToolBar* bar = new QToolBar("Main ToolBar");

    bar->addAction(QPixmap(":/img/Toolbar/newfile.ico"), "Создать файл", this, SLOT(slotNoImpl()));
    bar->addAction(QPixmap(":/img/Toolbar/openfile.ico"), "Открыть файл", this, SLOT(slotNoImpl()));
    bar->addSeparator();
    bar->addAction(QPixmap(":/img/Toolbar/save.ico"), "Сохранить", this, SLOT(slotNoImpl()));
    bar->addAction(QPixmap(":/img/Toolbar/saveas.ico"), "Сохранить как", this, SLOT(slotNoImpl()));
    bar->addSeparator();
    bar->addAction(QPixmap(":/img/Toolbar/image.ico"), "Вставить изображение", this, SLOT(slotNoImpl()));
    bar->addAction(QPixmap(":/img/Toolbar/link.ico"), "Вставить ссылку", this, SLOT(slotNoImpl()));
    bar->addSeparator();
    bar->addAction(QPixmap(":/img/Toolbar/tohtml.ico"), "Экспорт в html", this, SLOT(slotNoImpl()));
    bar->addAction(QPixmap(":/img/Toolbar/topdf.ico"), "Экспорт в pdf", this, SLOT(slotNoImpl()));

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

    html_ico->setCheckable(true);
    text_ico->setCheckable(true);
    markdown_ico->setCheckable(true);
    markdown_ico->setChecked(true);

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
        MarkdowntextEdit->setPlainText("MarkdowntextEdit");
        MarkdowntextEdit->show();
    }

}
void MainWindow::PreviewCheck()
{
    TextPreview->hide();
    if (text_ico->isChecked())
    {
        TextPreview->setText("TextPreview");
        TextPreview->show();
    }
}

void MainWindow::HtmlCheck()
{
    htmlPreview->hide();
    if (html_ico->isChecked())
    {
        htmlPreview->setText("htmlPreview");
        htmlPreview->show();
    }
}
