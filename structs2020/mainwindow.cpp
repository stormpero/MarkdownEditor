#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MarkdowntextEdit = new QPlainTextEdit;
    TextPreview = new QTextBrowser;
    htmlPreview = new QTextBrowser;
    ui->boxl->addWidget(MarkdowntextEdit);
    ui->boxl->addWidget(TextPreview);
    ui->boxl->addWidget(htmlPreview);
    TextPreview->hide();
    htmlPreview->hide();

    //Создание Toolbar
    addToolBar(Qt::TopToolBarArea,createMainToolBar());
    addToolBar(Qt::TopToolBarArea,createExtraToolBar());


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString a = "<h1> adfdf </h1>";
    ui->plainTextEdit->document()->setMarkdown(a);
}
