#include "mainwindow.h"

QToolBar* MainWindow::createNavigationToolBar()
{
    QToolBar* bar = new QToolBar("Navigation ToolBar");
    bar->addAction(QPixmap(":/img/Navigation_toolbar/bold.png"), "Жирный текст", this, SLOT(BoldText()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/italic.png"), "Курсив", this, SLOT(ItalicText()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/heading.png"), "Заголовок", this, SLOT(Heading()));

    bar->addAction(QPixmap(":/img/Navigation_toolbar/strikethrough.png"), "Зачёркнутый текст", this, SLOT(StrikeThrough()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/unordered_list.png"), "Неупорядоченный список", this, SLOT(UnorderedList()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/ordered_list.png"), "Упорядоченный список", this, SLOT(OrderedList()));

    bar->addAction(QPixmap(":/img/Navigation_toolbar/check_list.png"), "Контрольный лист", this, SLOT(CheckList()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/blockquote.png"), "Цитата", this, SLOT(BlockQuote()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/code.png"), "Код", this, SLOT(Code()));

    bar->addAction(QPixmap(":/img/Navigation_toolbar/table.png"), "Таблица", this, SLOT(Table()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/link.ico"), "Ссылка", this, SLOT(Link()));
    bar->addAction(QPixmap(":/img/Navigation_toolbar/image.ico"), "Вставить картинку", this, SLOT(Image()));

    bar->setLayoutDirection(Qt::LeftToRight);
    bar->setMovable(false);
    bar->setIconSize(QSize(16,16));

    return bar;
}

void MainWindow::BoldText()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("**"+ QString("strong text")+"**");
         cursor.setPosition(cursor.position() - 13);
         cursor.setPosition(cursor.position() + 11, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("**"+cursor.selectedText()+"**");
}
void MainWindow::ItalicText()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("*"+ QString("emphasized text")+"*");
         cursor.setPosition(cursor.position() - 16);
         cursor.setPosition(cursor.position() + 15, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("*"+cursor.selectedText()+"*");
}
void MainWindow::Heading()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    int size = 7;
    if(cursor.selectedText().size() == 0)
    {
         cursor.insertText("#" + QString("Heading"));
         cursor.setPosition(cursor.position() - size);
         cursor.setPosition(cursor.position() + size, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
    {
        int size = cursor.selectedText().size();
        cursor.insertText("#" + cursor.selectedText());
        cursor.setPosition(cursor.position() - size);
        cursor.setPosition(cursor.position() + size, QTextCursor::KeepAnchor);
        MarkdowntextEdit->setTextCursor(cursor);
    }
}
void MainWindow::StrikeThrough()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("~~"+ QString("strikethrough text")+"~~");
         cursor.setPosition(cursor.position() - 20);
         cursor.setPosition(cursor.position() + 18, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("~~"+cursor.selectedText()+"~~");
}
void MainWindow::UnorderedList()
{

}
void MainWindow::OrderedList()
{

}
void MainWindow::CheckList()
{

}
void MainWindow::BlockQuote()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
         cursor.insertText(">" + QString("Blockquote"));
         cursor.setPosition(cursor.position() - 10);
         cursor.setPosition(cursor.position() + 10, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
    {
        int size = cursor.selectedText().size();
        cursor.insertText(">" + cursor.selectedText());
        cursor.setPosition(cursor.position() - size);
        cursor.setPosition(cursor.position() + size, QTextCursor::KeepAnchor);
        MarkdowntextEdit->setTextCursor(cursor);
    }
}
void MainWindow::Code()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("```\n"+ QString("enter code here")+"\n```");
         cursor.setPosition(cursor.position() - 19);
         cursor.setPosition(cursor.position() + 15, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("```\n"+cursor.selectedText()+"\n```");
}
void MainWindow::Table()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("|  |  |  \n|---|---|  \n|  |  |");
         cursor.setPosition(cursor.position() - 28);
         cursor.setPosition(cursor.position() + 2, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("|" + cursor.selectedText()+ "|  |\n|---|---|  \n|  |  |");
}
void MainWindow::Link()
{
    bool ok;
    QString text = QInputDialog::getText( this,"Markdown Editor","Введите ссылку:",QLineEdit::Normal,"",&ok,Qt::Window);
    if (ok && !text.isEmpty())
         MarkdowntextEdit->insertPlainText(QString("[Название](%1)").arg(text));
    Preview->setOpenExternalLinks(true);
    Preview->setOpenLinks(true);
}
void MainWindow::Image()
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


