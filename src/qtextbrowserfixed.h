#ifndef TEXTBROWSERFIXED_H
#define TEXTBROWSERFIXED_H

#include <QTextBrowser>
#include <QEvent>
#include <QTextBlock>

/*!
 \brief Исправленный QTextBrowser

*/
class QTextBrowserFixed : public QTextBrowser
{

public:
    /*!
     \brief Конструктор

     \param parent
    */
    QTextBrowserFixed(QWidget *parent = nullptr);

    /*!
     \brief Исправленный ивент прокрутки колеса и сочетание ctrl + колесо мыши

     \param event
    */
    void wheelEvent(QWheelEvent *event) override;
};

#endif // TEXTBROWSERFIXED_H
