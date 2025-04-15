#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PlaylistManager.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/Source/View/Main.qml"));
    engine.load(url);
    return app.exec();
}