#include "standbymanager.h"

StandbyManager::StandbyManager(QObject *parent)
    : QObject(parent), m_interval(10000) {
    connect(&m_standbyTimer, &QTimer::timeout, this, &StandbyManager::turnOffScreen);
}

int StandbyManager::interval() const {
    return m_interval;
}

void StandbyManager::setInterval(int interval) {
    if (m_interval != interval) {
        m_interval = interval;
        emit intervalChanged();
        if (m_standbyTimer.isActive()) {
            startStandbyTimer();
        }
    }
}

void StandbyManager::startStandbyTimer() {
    qDebug() << Q_FUNC_INFO;
    m_standbyTimer.start(m_interval);
}

void StandbyManager::stopStandbyTimer() {
    m_standbyTimer.stop();
    turnOnScreen();
}

void StandbyManager::turnOffScreen() {
    std::cout << "turn off screen" << std::endl;
    system("xset dpms force off");
}

void StandbyManager::turnOnScreen() {
    system("xset dpms force on");
}

void StandbyManager::saveSettings(const QString &filePath) {
    QJsonObject json;
    json["interval"] = m_interval;

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return;
    }
    file.write(QJsonDocument(json).toJson());
    file.close();
}

void StandbyManager::loadSettings(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if (doc.isObject()) {
        QJsonObject json = doc.object();
        if (json.contains("interval") && json["interval"].isDouble()) {
            setInterval(json["interval"].toInt());
        }
    }
}

