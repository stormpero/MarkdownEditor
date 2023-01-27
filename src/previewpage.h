#ifndef PREVIEWPAGE_H
#define PREVIEWPAGE_H

#include <QWebEnginePage>
#include <QDesktopServices>

/*!
 \brief Страница, которая представляет переведённый в html код markdown

*/
class PreviewPage : public QWebEnginePage
{
    Q_OBJECT
public:
    /*!
     \brief Конструктор

     \param parent
    */
    explicit PreviewPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    /*!
     \brief Открывает ссылку

     \param url
     \param type
     \param isMainFrame
     \return bool
    */
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

#endif // PREVIEWPAGE_H
