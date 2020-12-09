#include "markdowntohtml.h"

MarkDownToHtml::MarkDownToHtml(QString input) : result(input)
{
    checkForHeadings();
}

void MarkDownToHtml::checkForHeadings()
{
    //QRegExp heading("\\b(#+) +.*\n");
    //result.replace(QRegExp("\\b(#+) +.*\n"), "<h1>\\1</h1>");
}

QString MarkDownToHtml::getResult()
{
    return result;
}
