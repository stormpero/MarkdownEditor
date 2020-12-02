#include "markdowntohtml.h"

MarkDownToHtml::MarkDownToHtml()
{
    rx = QRegExp("^[1-е]$");
}
