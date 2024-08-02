#include "NodeFlow.h"
#include "style.hpp"
#include <QTabWidget>
#include <QLabel>
#include <QTextEdit>
#include <QDateTime>

#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/GraphicsViewStyle>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/NodeStyle>

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

NodeFlow::NodeFlow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("NodeFlow");
    setMinimumSize(1080, 720);
    setNodeStyle();

    auto menuBar = new QMenuBar(this);
    QMenu *menu = menuBar->addMenu("File");
    auto saveAction = menu->addAction("Save Scene");

    QTabWidget *tabWidget = new QTabWidget(this);
    QLabel *label = new QLabel();//创建一个QLabel（QWidget*）
    QLabel *label2 = new QLabel();//
    label2->setText(u8"downdowndown");
    label->setText(u8"upupup");

    tabWidget->setTabPosition(QTabWidget::South);//将tabBar的位置放在左边
    tabWidget->show();

    QGraphicsView *graphicsView = new QGraphicsView(this);
    tabWidget->setTabShape(QTabWidget::Triangular);
    // tabWidget->addTab(vtkwidget_, "point cloud");
    tabWidget->addTab(graphicsView, "image");
    /*
    QDockWidget* dockwidget = new QDockWidget("Console", this);

	QTextEdit *console_text_ = new QTextEdit(this);
	QDateTime* data = new QDateTime(QDateTime::currentDateTime());
	
    dockwidget->setWindowTitle("Console");
	dockwidget->setWidget(console_text_);
    this->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockwidget);

    */
    // QWidget *flow_view = new QWidget(this);
    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();
    DataFlowGraphModel dataFlowGraphModel(registry);

    DataFlowGraphicsScene scene(dataFlowGraphModel);

    GraphicsView view(&scene);

    // QWidget *flow_view = new QWidget(this);
    // std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();
    // DataFlowGraphModel dataFlowGraphModel(registry);
    // auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, flow_view);
    // auto view = new GraphicsView(scene);

    setCentralWidget(tabWidget);
}


NodeFlow::~NodeFlow()
{

}