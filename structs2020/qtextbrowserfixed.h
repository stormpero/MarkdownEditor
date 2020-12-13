#ifndef TEXTBROWSERFIXED_H
#define TEXTBROWSERFIXED_H

#include <QTextBrowser>
#include <QEvent>
#include <QTextBlock>

class QTextBrowserFixed : public QTextBrowser
{
public:
    QTextBrowserFixed(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent *event) override;
};

#endif // TEXTBROWSERFIXED_H
