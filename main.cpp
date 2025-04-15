#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "AppController.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    AppController appController;
    engine.rootContext()->setContextProperty("appController", &appController);

    const QUrl url(QStringLiteral("qrc:/Source/View/Main.qml"));
    engine.load(url);

    return app.exec();
}