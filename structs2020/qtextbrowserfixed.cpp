#include "qtextbrowserfixed.h"
#include <QDebug>
QTextBrowserFixed::QTextBrowserFixed(QWidget *parent) : QTextBrowser(parent)
{}

void QTextBrowserFixed::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->delta() > 0)
        {
            if(this->font().pointSize() == 50)
                return;
        }
        else
        {
            if(this->font().pointSize() == 8)
                return;
        }
    }
    QTextBrowser::wheelEvent(event);
}
