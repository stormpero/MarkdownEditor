#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "markdowntohtml.h"

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
    disableMenu(true);

}

void MainWindow::InitialiseConnections()
{
    connect(MarkdowntextEdit, &QPlainTextEdit::textChanged, [this]()
    {
        if(!isChanged)
        {
            isChanged = true;
            setWindowTitle(QString("*%1 - Markdown Editor").arg(file.fileName().isEmpty() ? "new" : file.fileName()));
        }
        TextPreview->setMarkdown(MarkdowntextEdit->document()->toMarkdown());
        //htmlPreview->setHtml(TextPreview->document()->toHtml());
        htmlPreview->setText(MarkDownToHtml(TextPreview->document()->toRawText()).getResult());
    });

    //MenuBar
    connect(ui->action_newFile, SIGNAL(triggered()), this, SLOT(CreateNewFile()));
    connect(ui->action_openFile, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(ui->action_save, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->action_saveAs, SIGNAL(triggered()), this, SLOT(SaveFileAs()));
    connect(ui->action_link, SIGNAL(triggered()), this, SLOT(InsertLink()));
    connect(ui->action_img, SIGNAL(triggered()), this, SLOT(InsertImg()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

