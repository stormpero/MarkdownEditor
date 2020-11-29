#include "markdowntohtml.h"

MarkDownToHtml::MarkDownToHtml()
{
    rx = QRegExp("^[1-9][0-9]?[а-е]$");
}
