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
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 \brief Основной класс

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
     \brief Деструктор

    */
    ~MainWindow();


private:
    Ui::MainWindow *ui; /*!< Интерфейс программы */
    /*!
     \brief Иницилизация CSS стилей

    */
    void initializationCSS();
    /*!
     \brief Создание полей для текста

    */
    void IntitialiseApp();
    /*!
     \brief Создание панели инструментов

    */
    void CreateToolBars();
    /*!
     \brief Инициализация связей между объектами и кнопками

    */
    void InitialiseConnections();
    /*!
     \brief Отключение кнопок меню

     \param a
    */
    void disableMenu(bool a);
    /*!
     \brief Создание статус бара

    */
    void CreateStatusBar();
    /*!
     \brief Обновление размера файла

    */
    void updateFileSize();


private:
    /*!
     \brief Создание основной панели инструментов

     \return QToolBar
    */
    QToolBar* createMainToolBar();
    /*!
     \brief Создание кнопок

     \return QToolBar
    */
    QToolBar* createExtraToolBar();
    /*!
     \brief Создание дополнительной панели задач

     \return QToolBar
    */
    QToolBar* createWorkToolBar();

    QToolBar* createNavigationToolBar();


private:
    QToolBar *WorkToolBar; /*!< TODO: describe */
    Document m_content; /*!< TODO: describe */


private slots:
    /*!
     * \brief Отображение поля редактирования текста
     */
    void MarkdowneditCheck();
    /*!
     * \brief Отображение превью
     */
    void PreviewCheck();
    /*!
     * \brief Отображение предпросмотра HTML
     */
    void HtmlCheck();
    /*!
     \brief Создать новый файл

    */
    void CreateNewFile();
    /*!
     \brief Открыть файл

    */
    void OpenFile();
    /*!
     \brief Сохранить файл

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

private slots:
    //Navigation toolbar slots
    void BoldText();
    void ItalicText();
    void Heading();
    void StrikeThrough();
    void UnorderedList();
    void OrderedList();
    void CheckList();
    void BlockQuote();
    void Code();
    void Table();
    void Link();
    void Image();
private:
    /*!
     \brief Вывод диалогового окно

     \return int
    */
    int SaveDialog();



private:
    CodeEditor *MarkdowntextEdit; /*!< Редактор Markdown*/
    QTextBrowserFixed* Preview; /*!< Предпросмотр */
    QTextBrowserFixed* htmlPreview; /*!< Предпросмотр HTML */
    QWebEngineView* htmlWeb;

    QAction* html_ico; /*!< Кнопка отображения HTML */
    QAction* text_ico; /*!< Кнопка отображения текста */
    QAction* markdown_ico; /*!< Кнопка отображения редактора Markdown */

    QLabel* cursorPosition; /*!< Номер строки на которой находится курсор */
    QLabel* fileSize; /*!< Размер файла */


    QFile file; /*!< Файл с которым происходит работа */

    bool justCreated = false; /*!< Только что созданный файл, который не имеет пути */
    bool isChanged = false; /*!< Файл изменился */
};
#endif // MAINWINDOW_H
