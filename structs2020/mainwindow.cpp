#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set title & ico
    setWindowTitle("Markdown Editor");
    setWindowIcon(QIcon(":/img/window_ico.ico"));
    //Create Texteditors & Textviews

    QLabel * label = new QLabel();
    statusBar()->addWidget(label);

    initializationCSS();

    TextPreview->setReadOnly(true);
    htmlPreview->setReadOnly(true);

    MarkdowntextEdit = new QPlainTextEdit;
    TextPreview = new QTextBrowser;
    htmlPreview = new QTextBrowser;

    ui->boxl->addWidget(MarkdowntextEdit);
    ui->boxl->addWidget(TextPreview);
    ui->boxl->addWidget(htmlPreview);    
    MarkdowntextEdit->hide();
    TextPreview->hide();
    htmlPreview->hide();

    //Create Toolbar
    addToolBar(Qt::TopToolBarArea,createMainToolBar());
    WorkToolBar = createWorkToolBar();
    addToolBar(Qt::TopToolBarArea,WorkToolBar);
    addToolBar(Qt::TopToolBarArea,createExtraToolBar());
    WorkToolBar->setDisabled(true);

    TextPreview->setAcceptRichText(false);

    connect(MarkdowntextEdit, &QPlainTextEdit::textChanged, [this]()
    {
        isChanged = true;
        setWindowTitle(QString("*" + file.fileName() + " - Markdown Editor"));
        TextPreview->setMarkdown(MarkdowntextEdit->document()->toMarkdown());
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

