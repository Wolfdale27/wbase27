#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include "presetmanager.h"
#include "standbymanager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    PresetManager preset;
    qmlRegisterType<StandbyManager>("com.wbase27", 1, 0, "StandbyManager");

    const QUrl url(u"qrc:/wbase27/src/Main.qml"_qs);
        QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &app,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);
        engine.load(url);

        return app.exec();

}
