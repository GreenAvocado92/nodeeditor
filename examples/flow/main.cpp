#include "models.hpp"
#include "style.hpp"

#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/GraphicsViewStyle>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/NodeStyle>

#include <QtWidgets/QApplication>

#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QScreen>
#include <QDockWidget>
#include <QMainWindow>

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

    ret->registerModel<MyDataModel>();

    return ret;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setStyle();

    QMainWindow mainWindow;
    
    auto menuBar = new QMenuBar(&mainWindow);
    QMenu *menu = menuBar->addMenu("File");
    auto saveAction = menu->addAction("Save Scene");
    
    QDockWidget* console = new QDockWidget("AAAA");
    mainWindow.addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, console);
    QWidget flow_view;
    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();
    DataFlowGraphModel dataFlowGraphModel(registry);
    auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, &flow_view);
    auto view = new GraphicsView(scene);
    console->setWidget(view);

    mainWindow.show();
    return app.exec();
}
