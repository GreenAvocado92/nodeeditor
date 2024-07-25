#pragma once
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QScreen>
#include <QDockWidget>

class NodeFlow : public QMainWindow {
    Q_OBJECT

public:
    NodeFlow(QWidget* parent = nullptr);
    ~NodeFlow();
};