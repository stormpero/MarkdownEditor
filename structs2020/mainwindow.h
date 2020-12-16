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
#include "qtextbrowserfixed.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 \brief

*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     \brief Конструктор

     \param parent
    */
    MainWindow(QWidget *parent = nullptr);
    /*!
     \brief

    */
    ~MainWindow();


private:
    Ui::MainWindow *ui; /*!< TODO: describe */
    /*!
     \brief

    */
    void initializationCSS();
    /*!
     \brief

    */
    void IntitialiseApp();
    /*!
     \brief

    */
    void CreateToolBars();
    /*!
     \brief

    */
    void InitialiseConnections();
    /*!
     \brief

     \param a
    */
    void disableMenu(bool a);
    /*!
     \brief

    */
    void CreateStatusBar();
    /*!
     \brief

    */
    void updateFileSize();


private:
    /*!
     \brief

     \return QToolBar
    */
    QToolBar* createMainToolBar();
    /*!
     \brief

     \return QToolBar
    */
    QToolBar* createExtraToolBar();
    /*!
     \brief

     \return QToolBar
    */
    QToolBar* createWorkToolBar();


private:
    QToolBar *WorkToolBar; /*!< TODO: describe */
    Document m_content; /*!< TODO: describe */


private slots:
    /*!
     * \brief MarkdowneditCheck
     */
    void MarkdowneditCheck();
    void PreviewCheck();
    void HtmlCheck();
    /*!
     \brief

    */
    void CreateNewFile();
    /*!
     \brief

    */
    void OpenFile();
    /*!
     \brief

    */
    void SaveFile();
    /*!
     \brief Сохранить файл как

     \return int
    */
    int SaveFileAs();
    /*!
     \brief Вставить изображение

    */
    void InsertImg();
    /*!
     \brief Вставить ссылку

    */
    void InsertLink();
    /*!
     \brief Экспорт в PDF

    */
    void ExportToPDF();
    /*!
     \brief Экспорт в HTML

    */
    void ExportHtml();
    /*!
     \brief Информация о программе

    */
    void AboutProgram();
    /*!
     \brief Документация Markdown (англоязычная)

    */
    void MarkdownHelp();
    /*!
     \brief Функция проверки на несохранненный данные перед выходом

     \param event Ловим ивент выхода из программы
    */
    void closeEvent(QCloseEvent *event);

private:
    /*!
     \brief Вывод диалогового окно

     \return int
    */
    int SaveDialog();



private:
    CodeEditor *MarkdowntextEdit; /*! Редактор Markdown*/
    QTextBrowserFixed* TextPreview; /*!< TODO: describe */
    QTextBrowserFixed* htmlPreview; /*!< TODO: describe */

    QWebEngineView* htmlWeb; /*!< TODO: describe */



    QAction* html_ico; /*! Значок в */
    QAction* text_ico; /*!< TODO: describe */
    QAction* markdown_ico; /*!< TODO: describe */


    QLabel* cursorPosition; /*!< Номер на которой находится курсор */
    QLabel* fileSize; /*!< Размер файла */


    QFile file; /*! Файл с которым происходит работа */

    bool isLoadFinished = false; /*!< TODO: describe */
    bool justCreated = false; /*! Файл созданный в программме, н */
    bool isChanged = false; /*!< TODO: describe */
};
#endif // MAINWINDOW_H
