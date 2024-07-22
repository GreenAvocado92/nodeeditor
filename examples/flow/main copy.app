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
    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();

    QWidget mainWidget;

    auto menuBar = new QMenuBar();
    QMenu *menu = menuBar->addMenu("File");

    auto saveAction = menu->addAction("Save Scene");
    saveAction->setShortcut(QKeySequence::Save);

    auto loadAction = menu->addAction("Load Scene");
    loadAction->setShortcut(QKeySequence::Open);

    QVBoxLayout *l = new QVBoxLayout(&mainWidget);

    DataFlowGraphModel dataFlowGraphModel(registry);

    l->addWidget(menuBar);
    auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, &mainWidget);

    auto view = new GraphicsView(scene);
    l->addWidget(view);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);

    QDockWidget *console = new QDockWidget("console");
    console->setAllowedAreas(Qt::BottomDockWidgetArea);
    console->setFixedHeight(20);
    l->addWidget(console);

    // QDockWidget *tree = new QDockWidget("Tree", & mainWidget);

    // QObject::connect(saveAction, &QAction::triggered, scene, [scene, &mainWidget]() {
    //     if (scene->save())
    //         mainWidget.setWindowModified(false);
    // });

    // QObject::connect(loadAction, &QAction::triggered, scene, &DataFlowGraphicsScene::load);

    // QObject::connect(scene, &DataFlowGraphicsScene::sceneLoaded, view, &GraphicsView::centerScene);

    // QObject::connect(scene, &DataFlowGraphicsScene::modified, &mainWidget, [&mainWidget]() {
    //     mainWidget.setWindowModified(true);
    // });

    mainWidget.setWindowTitle("Data Flow");
    mainWidget.resize(960, 720);
    // Center window.
    mainWidget.move(QApplication::primaryScreen()->availableGeometry().center()
                    - mainWidget.rect().center());
    mainWidget.showNormal();

    return app.exec();
}
