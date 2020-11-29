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
    MarkdowntextEdit->hide();
    TextPreview->hide();
    htmlPreview->hide();
    //Создание Toolbar
    addToolBar(Qt::TopToolBarArea,createMainToolBar());
    WorkToolBar = createWorkToolBar();
    addToolBar(Qt::TopToolBarArea,WorkToolBar);
    addToolBar(Qt::TopToolBarArea,createExtraToolBar());
    WorkToolBar->setDisabled(true);
    connect(MarkdowntextEdit, &QPlainTextEdit::textChanged, [this]() { TextPreview->setMarkdown(MarkdowntextEdit->toPlainText()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

