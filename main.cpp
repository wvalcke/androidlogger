#include <QtWidgets/QApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtAndroid>
#include "DataPool.h"
#include "LockHelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DataPool::registerMetaData();
    DataPool loDataPool;

    engine.rootContext()->setContextProperty("DataPool", &loDataPool);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QtAndroid::androidActivity().callStaticMethod<void>("org/bep/jni/ScreenLockInterface", "initializeData", "()V");

    return app.exec();
}
