#pragma once

#include "DecimalData.hpp"
#include "MathOperationDataModel.hpp"

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class DivisionModel : public MathOperationDataModel
{
public:
    DivisionModel();

    virtual ~DivisionModel() {}

public:
    QString caption() const override { return QStringLiteral("Division"); }

    bool portCaptionVisible(PortType portType, PortIndex portIndex) const override
    {
        Q_UNUSED(portType);
        Q_UNUSED(portIndex);
        return true;
    }

    QString portCaption(PortType portType, PortIndex portIndex) const override
    {
        switch (portType) {
        case PortType::In:
            if (portIndex == 0)
                return QStringLiteral("Dividend");
            else if (portIndex == 1)
                return QStringLiteral("Divisor");

            break;

        case PortType::Out:
            return QStringLiteral("Result");

        default:
            break;
        }
        return QString();
    }

    QString name() const override { return QStringLiteral("Division"); }
    QWidget *embeddedWidget() override { return _label; }
    bool resizable() const override { return true; }

private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;

        auto n1 = _number1.lock();
        auto n2 = _number2.lock();

        if (n2 && (n2->number() == 0.0)) {
            //modelValidationState = NodeValidationState::Error;
            //modelValidationError = QStringLiteral("Division by zero error");
            _result.reset();
        } else if (n1 && n2) {
            //modelValidationState = NodeValidationState::Valid;
            //modelValidationError = QString();
            _result = std::make_shared<DecimalData>(n1->number() / n2->number());
        } else {
            //modelValidationState = NodeValidationState::Warning;
            //modelValidationError = QStringLiteral("Missing or incorrect inputs");
            _result.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }

private:
    QLabel *_label;

protected:
    bool eventFilter(QObject *object, QEvent *event) override;
};

DivisionModel::DivisionModel()
    : _label(new QLabel("P"))
{
    _label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    _label->setMinimumSize(15, 15);
    _label->setMaximumSize(20, 20);

    _label->installEventFilter(this);
}

bool DivisionModel::eventFilter(QObject *object, QEvent *event)
{
    if (object == _label) {
        int w = _label->width();
        int h = _label->height();
        switch (event->type()) {
            case QEvent::MouseButtonPress: {
                qDebug() << " Mouse button pressed";
                QMessageBox message(QMessageBox::NoIcon, "Params", "Undefined Params"); 
                message.setFixedSize(100, 250);
                message.exec();
                break;
            }
            case QEvent::MouseButtonRelease:
                qDebug() << "Mouse button released";
                break;
            case QEvent::MouseButtonDblClick:
                qDebug() << "Mouse double clicked";
                // 处理鼠标双击事件
                break;
        }
        return false;
    }
}