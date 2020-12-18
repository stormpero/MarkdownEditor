#ifndef PREVIEWPAGE_H
#define PREVIEWPAGE_H

#include <QWebEnginePage>
#include <QDesktopServices>

/*!
 \brief

*/
class PreviewPage : public QWebEnginePage
{
    Q_OBJECT
public:
    /*!
     \brief

     \param parent
    */
    explicit PreviewPage(QObject *parent = nullptr) : QWebEnginePage(parent) {}

protected:
    /*!
     \brief

     \param url
     \param type
     \param isMainFrame
     \return bool
    */
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

#endif // PREVIEWPAGE_H
