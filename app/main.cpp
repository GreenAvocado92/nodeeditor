#include "NodeFlow.h"

#include <QApplication>
#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/GraphicsViewStyle>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/NodeStyle>

#include "style.hpp"
#include "ImageLoaderModel.hpp"

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::GraphicsViewStyle;
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::NodeStyle;

static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();
    ret->registerModel<ImageLoaderModel>();
    // ret->registerModel<TestModel>();

    return ret;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // NodeFlow w;
    // w.show();
    QMainWindow mainWindow;
    
    setNodeStyle();

    auto menuBar = new QMenuBar(&mainWindow);
    menuBar->setGeometry(0,0, mainWindow.width(), 50);
    QMenu *menu = menuBar->addMenu("File");
    auto saveAction = menu->addAction("Save Scene");
    auto loadAction = menu->addAction("Load Scene");

    QDockWidget* flow_dock = new QDockWidget("Flow");
    mainWindow.addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, flow_dock);
    QWidget flow_view;
    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();
    DataFlowGraphModel dataFlowGraphModel(registry);
    auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, &flow_view);
    auto view = new GraphicsView(scene);
    flow_dock->setWidget(view);

    QDockWidget* console = new QDockWidget("输出");
    console->setFixedHeight(150);
    mainWindow.addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, console);
    
    QDockWidget* properties = new QDockWidget("Property");
    properties->setFixedWidth(200);
    mainWindow.addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, properties);

    mainWindow.setCentralWidget(flow_dock);
    mainWindow.show();

    return a.exec();
}