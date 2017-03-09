#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QQmlContext>

#include "gcodegenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    GCodeGenerator gcodeGenerator;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("gcodeGenerator", &gcodeGenerator);

    return app.exec();
}
