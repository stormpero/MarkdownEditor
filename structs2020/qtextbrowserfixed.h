#ifndef TEXTBROWSERFIXED_H
#define TEXTBROWSERFIXED_H

#include <QTextBrowser>
#include <QEvent>
#include <QTextBlock>

/*!
 \brief

*/
class QTextBrowserFixed : public QTextBrowser
{
public:
    /*!
     \brief

     \param parent
    */
    QTextBrowserFixed(QWidget *parent = nullptr);

    /*!
     \brief

     \param event
    */
    void wheelEvent(QWheelEvent *event) override;
};

#endif // TEXTBROWSERFIXED_H
