#include "mainwindow.h"

int MainWindow::SaveDialog()
{
    if(isChanged)
    {
        int k = QMessageBox::warning(this, tr("Markdown Editor"),
                                     tr("Документ был изменён\n"
                                        "Вы хотите сохранить свои изменения?"),
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);

        if (k == QMessageBox::Save)
            SaveFile();

        else if (k == QMessageBox::Cancel)
            return -1;
    }
    return 0;
}

void MainWindow::WheelExpansion(QObject *object, QEvent *event)
{
    if(object == MarkdowntextEdit  && event->type() == QEvent::Wheel )
    {
        QWheelEvent *wheel = static_cast<QWheelEvent*>(event);
        if( wheel->modifiers() == Qt::ControlModifier )
            if(wheel->delta() > 0)
            {
                MarkdowntextEdit->zoomIn(2);
            }
            else
            {
                MarkdowntextEdit->zoomOut(2);
            }
    }
}