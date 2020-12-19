#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QString>

/*!
 \brief Класс документ. Используется для получения html кода страницы

*/
class Document : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text MEMBER m_text NOTIFY textChanged FINAL)
public:
    /*!
     \brief Конструктор

     \param parent
    */
    explicit Document(QObject *parent = nullptr) : QObject(parent) {}

    /*!
     \brief Ставит текст в m_text

     \param text
    */
    void setText(const QString &text);

signals:
    /*!
     \brief Если текст изменится

     \param text
    */
    void textChanged(const QString &text);

private:
    QString m_text; /*!< Текст, который будет передаваться в index.html для дальнейшего преобразование в html код */
};

#endif // DOCUMENT_H
