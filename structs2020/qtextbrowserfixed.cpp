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
            if(this->font().pointSize() != 50)
                this->zoomIn(1);
            else
                return;
        }
        else
        {
            if(this->font().pointSize() != 8)
                this->zoomOut(1);
            else
                return;
        }
    }
    QTextBrowser::wheelEvent(event);
}
