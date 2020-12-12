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

    bar->addAction(QPixmap(":img/Toolbar/save.ico"), "Сохранить", this, SLOT(SaveFile()));
    bar->addAction(QPixmap(":img/Toolbar/saveas.ico"), "Сохранить как", this, SLOT(SaveFileAs()));

    bar->addSeparator();

    bar->addAction(QPixmap(":/img/Toolbar/image.ico"), "Вставить изображение", this, SLOT(InsertImg()));
    bar->addAction(QPixmap(":/img/Toolbar/link.ico"), "Вставить ссылку", this, SLOT(InsertLink()));

    bar->addSeparator();

    bar->addAction(QPixmap(":/img/Toolbar/topdf.ico"), "Экспорт в pdf", this, SLOT(ExportToPDF()));
    bar->addAction(QPixmap(":/img/Toolbar/tohtml.ico"), "Экспорт в html", this, SLOT(ExportHtml()));

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
    isEnableTextPreview = false;
    if (text_ico->isChecked())
    {
        TextPreview->show();
        isEnableTextPreview = true;
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

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);    
    WorkToolBar->setDisabled(false);

    disableMenu(false);

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

    setWindowTitle(QString("%1 - Markdown Editor").arg(file.fileName()));

    markdown_ico->setDisabled(false);
    html_ico->setDisabled(false);
    text_ico->setDisabled(false);
    WorkToolBar->setDisabled(false);

    disableMenu(false);

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

    if (isExistButNoWay)
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
    isExistButNoWay = false;
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

    isChanged = false;
    isExistButNoWay = false;

    return 1;
}

void MainWindow::InsertImg()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Выберите картинку", QDir::homePath(), "Images (*.png *.xpm *.jpg)");
    if(filePath.isEmpty())
    {
        qDebug() << "Read and write paths are empty";
        return;
    }
    QFileInfo img(filePath);
    QString fileName = img.fileName();
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    MarkdowntextEdit->insertPlainText(QString("![%2](%1)").arg(filePath).arg(fileName.left(fileName.indexOf("."))));
}

void MainWindow::InsertLink()
{
    bool ok;
    QString text = QInputDialog::getText( this,
                                          "Markdown Editor",
                                          "Введите ссылку:",
                                          QLineEdit::Normal,
                                          "",
                                          &ok,
                                          Qt::Window
                                         );
    if (ok && !text.isEmpty())
         MarkdowntextEdit->insertPlainText(QString("[Название](%1)").arg(text));
}

void MainWindow::ExportToPDF()
{
     QString filePath = QFileDialog::getSaveFileName(0, "Экспорт в PDF","", "*.pdf");
     if(filePath.isEmpty())
     {
         qDebug() << "Read and write paths are empty";
         return;
     }
     QPrinter printer;
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName(filePath); // устанавливаем путь к pdf файлу

     TextPreview->print(&printer);
}
void MainWindow::ExportHtml()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Экспорт","", "*.html");

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
    file.write(htmlPreview->toPlainText().toStdString().data());
    file.close();
}


