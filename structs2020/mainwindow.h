#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QtWidgets>
//------------------//

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

private:
    QToolBar* createMainToolBar();
    QToolBar* createExtraToolBar();

private slots:
    void MarkdowneditCheck();
    void PreviewCheck();
    void HtmlCheck();



private:
    QPlainTextEdit *MarkdowntextEdit;
    QTextBrowser* TextPreview;
    QTextBrowser* htmlPreview;
    //Иконки
    QAction* html_ico;
    QAction* text_ico;
    QAction* markdown_ico;
};
#endif // MAINWINDOW_H
