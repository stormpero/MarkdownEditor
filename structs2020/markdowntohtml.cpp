#include "markdowntohtml.h"

MarkDownToHtml::MarkDownToHtml(QString input) : result(input)
{
    checkForHeadings();
}

void MarkDownToHtml::checkForHeadings()
{
    QRegExp heading("#+ (.*)\b");
    QStringList preResult;

    int pos = 0;

     while ((pos = heading.indexIn(result, pos)) != -1) {
         preResult << heading.cap(1);
         pos += heading.matchedLength();
     }

     for(int i = 0; i < preResult.size(); i++)
     {
         result = result + "<h" + QString::number(preResult[i].size()) + ">" +
                 preResult[i] +
                 "</h" + QString::number(preResult[i].size()) + ">\n";
     }
}

QString MarkDownToHtml::getResult()
{
    return result;
}
