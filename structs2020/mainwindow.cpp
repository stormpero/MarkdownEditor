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

    IntitialiseApp();
    initializationCSS();

    //Create Toolbars
    CreateToolBars();

    //Make connections to events
    InitialiseConnections();
}

void MainWindow::IntitialiseApp()
{
    MarkdowntextEdit = new CodeEditor;
    TextPreview = new QTextBrowser;
    htmlPreview = new QTextBrowser;
    TextPreview->setReadOnly(true);
    htmlPreview->setReadOnly(true);

    ui->boxl->addWidget(MarkdowntextEdit);
    ui->boxl->addWidget(TextPreview);
    ui->boxl->addWidget(htmlPreview);
    MarkdowntextEdit->hide();
    TextPreview->hide();
    htmlPreview->hide();
    MarkdowntextEdit->installEventFilter(this);
}

void MainWindow::CreateToolBars()
{
    addToolBar(Qt::TopToolBarArea,createMainToolBar());
    WorkToolBar = createWorkToolBar();
    addToolBar(Qt::TopToolBarArea,WorkToolBar);
    addToolBar(Qt::TopToolBarArea,createExtraToolBar());
    WorkToolBar->setDisabled(true);
}

void MainWindow::InitialiseConnections()
{
    connect(MarkdowntextEdit, &QPlainTextEdit::textChanged, [this]()
    {
        if(!isChanged)
        {
            isChanged = true;
            emit MainWindow::ifChanged();
        }
        TextPreview->setMarkdown(MarkdowntextEdit->document()->toMarkdown());
    });
    connect(this, &MainWindow::ifChanged, [this]()
    {
        setWindowTitle(QString("*%1 - Markdown Editor").arg(file.fileName().isEmpty() ? "new" : file.fileName()));
    });
}


MainWindow::~MainWindow()
{
    delete ui;
}

