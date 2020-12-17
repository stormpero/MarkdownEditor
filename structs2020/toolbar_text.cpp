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
    bar->setIconSize(QSize(15,15));

    return bar;
}

void MainWindow::BoldText()
{
    QTextCursor cursor = MarkdowntextEdit->textCursor();
    if(cursor.selectedText().size() == 0)
    {
        qDebug() << cursor.position();
        cursor.insertText("**"+ QString("strongText")+"**");
         cursor.setPosition(cursor.position() - 12);
         cursor.setPosition(cursor.position() + 10, QTextCursor::KeepAnchor);
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
         cursor.setPosition(cursor.position() - 11);
         cursor.setPosition(cursor.position() + 9, QTextCursor::KeepAnchor);
         MarkdowntextEdit->setTextCursor(cursor);
    }
    else
        cursor.insertText("*"+cursor.selectedText()+"*");
}
void MainWindow::Heading()
{

}
void MainWindow::StrikeThrough()
{

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

}
void MainWindow::Code()
{

}
void MainWindow::Table()
{

}
void MainWindow::Link()
{

}
void MainWindow::Image()
{

}


