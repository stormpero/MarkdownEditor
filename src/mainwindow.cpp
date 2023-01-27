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

    Preview->setOpenLinks(false);
    Preview->setOpenExternalLinks(false);

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

    connect(Preview, &QTextBrowser::anchorClicked, [](const QUrl &link)
    {
        QDesktopServices::openUrl(link);
    });
    connect(MarkdowntextEdit, &CodeEditor::blockCountChanged, [this]()
    {
        QTextCursor cursor = MarkdowntextEdit->textCursor();
        if(cursor.blockNumber() != 0)
        {
            if(MarkdowntextEdit->document()->findBlockByLineNumber( cursor.blockNumber() ).text().size() != 0)
                return;
            const QString text = MarkdowntextEdit->document()->findBlockByLineNumber( cursor.blockNumber() - 1 ).text();
            if(text.size() > 5
                    && text[0] == '-'
                    && text[1] == ' '
                    && text[2] == '['
                    && text[3] == ' '
                    && text[4] == ']'
                    && text[5] == ' ')
            {
                cursor.setPosition(cursor.block().position());
                cursor.insertText("- [ ] List item");
                cursor.setPosition(cursor.block().position() + 6);
                cursor.setPosition(cursor.block().position() + 15, QTextCursor::KeepAnchor);
                MarkdowntextEdit->setTextCursor(cursor);
            }
            else if(text.size() > 1 && text[0] == '-' && text[1] == ' ')
            {
                cursor.setPosition(cursor.block().position());
                cursor.insertText("- List item");
                cursor.setPosition(cursor.block().position() + 2);
                cursor.setPosition(cursor.block().position() + 11, QTextCursor::KeepAnchor);
                MarkdowntextEdit->setTextCursor(cursor);
            }
            else
            {
                QRegExp digits("^(\\d*)");
                digits.indexIn(text);
                if(digits.cap(1).size() != 0)
                {
                    if(text.size() >(digits.cap(1).size() + 1) &&
                            text[digits.cap(1).size()] == '.' &&
                            text[digits.cap(1).size() + 1] == ' ')
                    {
                        QString number = QString::number(digits.cap(1).toInt() + 1);
                        cursor.setPosition(cursor.block().position());
                        cursor.insertText(number + ". List item");
                        cursor.setPosition(cursor.block().position() + number.size() + 2);
                        cursor.setPosition(cursor.block().position() + number.size() + 11, QTextCursor::KeepAnchor);
                        MarkdowntextEdit->setTextCursor(cursor);
                    }
                }
            }
        }

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

