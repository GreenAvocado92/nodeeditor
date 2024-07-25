#include "TestModel.hpp"

#include <QtCore/QDir>
#include <QtCore/QEvent>

#include <QtWidgets/QFileDialog>

TestModel::TestModel()
    : _label(new QLabel("Double click to load image"))
{
    _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    QFont f = _label->font();
    f.setBold(true);
    f.setItalic(true);

    _label->setFont(f);

    _label->setMinimumSize(200, 200);
    _label->setMaximumSize(500, 300);

    _label->installEventFilter(this);
}

unsigned int TestModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

bool TestModel::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label) {
        int w = _label->width();
        int h = _label->height();
        // QEvent::MouseButtonPress
        if (event->type() == QEvent::MouseButtonPress) {
            QDialog *dialog = new QDialog();
            dialog->setWindowTitle("Params");
            dialog->setFixedSize(200, 300);
            dialog->show();
            Q_EMIT dataUpdated(0);

            return true;
        } else if (event->type() == QEvent::Resize) {
            if (!_pixmap.isNull())
                _label->setPixmap(_pixmap.scaled(w, h, Qt::KeepAspectRatio));
        }
    }

    return false;
}

NodeDataType TestModel::dataType(PortType const, PortIndex const) const
{
    return PixmapData().type();
}

std::shared_ptr<NodeData> TestModel::outData(PortIndex)
{
    return std::make_shared<PixmapData>(_pixmap);
}
