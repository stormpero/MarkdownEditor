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
    TextPreview = new QTextBrowserFixed;
    htmlPreview = new QTextBrowserFixed;

    htmlWeb = new QWebEngineView;

    PreviewPage *page = new PreviewPage(this);
    htmlWeb->setPage(page);


    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);


    htmlWeb->setUrl(QUrl("qrc:/index.html"));

    ui->boxl->addWidget(MarkdowntextEdit);
    ui->boxl->addWidget(TextPreview);
    ui->boxl->addWidget(htmlPreview);

    MarkdowntextEdit->hide();
    TextPreview->hide();
    htmlPreview->hide();

    //MarkdowntextEdit->installEventFilter(this);
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
    connect(MarkdowntextEdit, &CodeEditor::textChanged,
            [this]()
    {
        if(!isChanged)
        {
            isChanged = true;
            setWindowTitle(QString("*%1 - Markdown Editor").arg(file.fileName().isEmpty() ? "new" : file.fileName()));
        }
        // Check if htmlPreview or TextPreview are visible. Only after that convert the text
        if(htmlPreview->isVisible())
        {
            m_content.setText(MarkdowntextEdit->toPlainText());
            htmlWeb->page()->runJavaScript("document.documentElement.outerHTML", [this](const QVariant &v)
            {
                QRegExp rxlen("<div id=\"placeholder\">(.*)</div>");
                rxlen.indexIn(v.toString());
                htmlPreview->setPlainText(rxlen.cap(1));
            });
        }
        if(TextPreview->isVisible())
        {
            TextPreview->setMarkdown(MarkdowntextEdit->toPlainText());
        }
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

