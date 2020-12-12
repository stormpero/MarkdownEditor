#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QtWidgets>
#include <QPrinter>
#include <QWebEngineView>
#include <QWebChannel>

#include "previewpage.h"
#include "document.h"
#include "codeeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//show window and design functions
private:
    Ui::MainWindow *ui;
    void initializationCSS();
    void IntitialiseApp();
    void CreateToolBars();
    void InitialiseConnections();
    void disableMenu(bool a);

//Toolbar functions
private:
    QToolBar* createMainToolBar();
    QToolBar* createExtraToolBar();
    QToolBar* createWorkToolBar();

//Toolbar variable to set it enabled or disabled when needed
private:
    QToolBar *WorkToolBar;
    Document m_content;

//Toolbar buttons
private slots:
    void MarkdowneditCheck();
    void PreviewCheck();
    void HtmlCheck();
    void CreateNewFile();
    void OpenFile();
    void SaveFile();
    int SaveFileAs();
    void InsertImg();
    void InsertLink();
    void ExportToPDF();
    void ExportHtml();

//popup Windows
public:
    int SaveDialog();
    void WheelExpansion(QObject *object, QEvent *event);

//Other variables
public:
    CodeEditor *MarkdowntextEdit;
    QTextBrowser* TextPreview;
    bool isEnableTextPreview = false;
    QTextBrowser* htmlPreview;
    QWebEngineView* htmlWeb;

    //Иконки
    QAction* html_ico;
    QAction* text_ico;
    QAction* markdown_ico;

    //Файл, с которым происходит работа
    QFile file;
    bool isLoadFinished = false;
    bool isExistButNoWay = false;
    bool isChanged = false;
};
#endif // MAINWINDOW_H
