#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>

/*!
 \brief

*/
class Document : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged FINAL)
public:
    /*!
     \brief

     \param parent
    */
    explicit Document(QObject *parent = nullptr) : QObject(parent) {}

    /*!
     \brief

     \param text
    */
    void setText(const QString &text);

signals:
    /*!
     \brief

     \param text
    */
    void textChanged(const QString &text);

private:
    QString m_text; /*!< TODO: describe */
};

#endif // DOCUMENT_H
