#include <QtQml>
#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQuickView>
#include <QQuickItem>
#include <QVariantMap>

#include <unistatscore/Config.h>
#include "controller.h"

int main(int argc, char *argv[])
{
    std::string cfgPath = "/home/goldim/config.ini";
    if (argc == 2)
    {
        cfgPath = argv[1];
    }

//    controller cr(cfgPath);

    Config cfg(cfgPath);
    controller cr(cfg);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/appicon.png"));
    QQmlApplicationEngine engine;        
    engine.rootContext()->setContextProperty("_controller", &cr);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
