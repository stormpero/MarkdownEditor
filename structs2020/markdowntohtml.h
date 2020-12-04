#ifndef MARKDOWNTOHTML_H
#define MARKDOWNTOHTML_H

#include <QPlainTextEdit>
#include <QRegExp>
class MarkDownToHtml
{
private:
    QString result;
public:
    MarkDownToHtml(QString input);
    QString getResult();
private:
    void checkForHeadings();
};

#endif // MARKDOWNTOHTML_H
