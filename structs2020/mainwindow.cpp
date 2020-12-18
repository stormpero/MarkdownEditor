#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

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

    //Create Toolbars
    CreateToolBars();

    //Create StatusBar
    CreateStatusBar();

    //Make connections to events
    InitialiseConnections();

    initializationCSS();
}

void MainWindow::IntitialiseApp()
{
    MarkdowntextEdit = new CodeEditor;
    Preview = new QTextBrowserFixed;
    htmlPreview = new QTextBrowserFixed;
    htmlWeb = new QWebEngineView;

    PreviewPage *page = new PreviewPage(this);
    htmlWeb->setPage(page);

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);

    htmlWeb->setUrl(QUrl("qrc:/index.html"));

    ui->horizontalLayout->addWidget(MarkdowntextEdit);
    ui->horizontalLayout->addWidget(Preview);
    ui->horizontalLayout->addWidget(htmlPreview);

    MarkdowntextEdit->hide();
    Preview->hide();
    htmlPreview->hide();
}

void MainWindow::CreateToolBars()
{
    addToolBar(Qt::TopToolBarArea,createMainToolBar());
    WorkToolBar = createWorkToolBar();
    addToolBar(Qt::TopToolBarArea,WorkToolBar);
    addToolBar(Qt::TopToolBarArea,createExtraToolBar());
    addToolBarBreak();
    TextToolBar = createNavigationToolBar();
    addToolBar(Qt::TopToolBarArea, TextToolBar);
    WorkToolBar->setDisabled(true);
    TextToolBar->setDisabled(true);
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
            setWindowTitle(QString("*%1 - Markdown Editor").arg(justCreated ? "new" : file.fileName()));
        }
        // Check if htmlPreview or Preview are visible. Only after that convert the text
        if(Preview->isVisible())
        {
            Preview->setMarkdown(MarkdowntextEdit->toPlainText());
        }
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
        updateFileSize();
    });
    connect(MarkdowntextEdit, &CodeEditor::cursorPositionChanged,
            [this]()
    {
        cursorPosition->setText(QString("Строка: " + QString::number(MarkdowntextEdit->textCursor().blockNumber() + 1)));
    });

    //MenuBar
    connect(ui->action_newFile, SIGNAL(triggered()), this, SLOT(CreateNewFile()));
    connect(ui->action_openFile, SIGNAL(triggered()), this, SLOT(OpenFile()));

    connect(ui->action_save, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->action_saveAs, SIGNAL(triggered()), this, SLOT(SaveFileAs()));

    connect(ui->action_link, SIGNAL(triggered()), this, SLOT(Link()));
    connect(ui->action_img, SIGNAL(triggered()), this, SLOT(Image()));

    connect(ui->action_markdownhelp, SIGNAL(triggered()), this, SLOT(MarkdownHelp()));
    connect(ui->action_aboutProgram, SIGNAL(triggered()), this, SLOT(AboutProgram()));

    connect(ui->action_exit, SIGNAL(triggered()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

