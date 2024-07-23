#include "models.hpp"
#include <QEvent>
#include <QDialog>
// For some reason CMake could not generate moc-files correctly
// without having a cpp for an QObject from hpp.
bool MyDataModel::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QDialog *dialog = new QDialog();
        dialog->setWindowTitle("Params");
        dialog->setFixedSize(200, 300);
        dialog->show();
    }
    return true;
}