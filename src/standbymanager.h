#ifndef STANDBYMANAGER_H
#define STANDBYMANAGER_H

#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>
#include <cstdlib>
#include <QDebug>
#include <iostream>

class StandbyManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)

public:
    explicit StandbyManager(QObject *parent = nullptr);
    int interval() const;
    void setInterval(int interval);

    Q_INVOKABLE void saveSettings(const QString &filePath);
    Q_INVOKABLE void loadSettings(const QString &filePath);

public slots:
    void startStandbyTimer();
    void stopStandbyTimer();
    void turnOffScreen();
    void turnOnScreen();

signals:
    void intervalChanged();

private:
    int m_interval;
    QTimer m_standbyTimer;
};

#endif // STANDBYMANAGER_H
