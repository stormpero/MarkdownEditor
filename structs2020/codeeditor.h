#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QPainter>
#include <QTextBlock>
#include <QEvent>

class LineNumberArea;


/*!
 \brief

*/
class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    /*!
     \brief

     \param parent
    */
    CodeEditor(QWidget *parent = nullptr);

    /*!
     \brief

     \param event
    */
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    /*!
     \brief

     \return int
    */
    int lineNumberAreaWidth();
    /*!
     \brief

     \param event
    */
    void wheelEvent(QWheelEvent *event) override;
protected:
    /*!
     \brief

     \param event
    */
    void resizeEvent(QResizeEvent *event) override;

private slots:
    /*!
     \brief

     \param newBlockCount
    */
    void updateLineNumberAreaWidth(int newBlockCount);
    /*!
     \brief

    */
    void highlightCurrentLine();
    /*!
     \brief

     \param rect
     \param dy
    */
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    QWidget *lineNumberArea; /*!< TODO: describe */
    int lineNumberAreaFontSize = 8; /*!< TODO: describe */

    QPainter *painter; /*!< TODO: describe */


};

/*!
 \brief

*/
class LineNumberArea : public QWidget
{
public:
    /*!
     \brief

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
