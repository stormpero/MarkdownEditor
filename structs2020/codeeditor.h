#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QEvent>

class LineNumberArea;


/*!
 \brief Переопределённый класс QPlainTextEdit, в котором добавляется lineNumberArea

*/
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    /*!
     \brief Конструктор

     \param parent
    */
    CodeEditor(QWidget *parent = nullptr);

    /*!
     \brief Переопределённый метод отображения текстового поля, в котором обрабатывается "рисуется" lineNumberArea

     \param event
    */
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    /*!
     \brief Здесь рассчитывается ширина lineNumberArea

     \return int
    */
    int lineNumberAreaWidth();
    /*!
     \brief Переопределённый ивент прокутки колёсика мыши. В нём добавлено сочетание клавиш ctrl + колёсико мыши(увеличения изображения)

     \param event
    */
    void wheelEvent(QWheelEvent *event) override;
protected:
    /*!
     \brief Здесь выставляется рассчитанная ширина lineNumberArea

     \param event
    */
    void resizeEvent(QResizeEvent *event) override;

private slots:
    /*!
     \brief Обновить ширину lineNumberArea

     \param newBlockCount
    */
    void updateLineNumberAreaWidth(int newBlockCount);
    /*!
     \brief Подсвечивание текущей линии

    */
    void highlightCurrentLine();
    /*!
     \brief Обновить lineNumberArea

     \param rect
     \param dy
    */
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea; /*!< Сам виджет lineNumberArea */
    int lineNumberAreaFontSize = 8; /*!< Размер шрифта lineNumberArea */

    QPainter *painter; /*!< Рисовальщик */


};

/*!
 \brief Класс, который хранит настройки lineNumberArea

*/
class LineNumberArea : public QWidget
{
public:
    /*!
     \brief Конструктор

     \param editor
    */
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {}

    /*!
     \brief

     \return QSize
    */
    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    /*!
     \brief

     \param event
    */
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor; /*!< TODO: describe */
};

#endif
