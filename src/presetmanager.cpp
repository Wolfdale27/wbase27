#include "presetmanager.h"

PresetManager::PresetManager() {
    openConfig();
}

PresetManager& PresetManager::Instance()
{
    static PresetManager manager;
    return manager;
}

bool PresetManager::openConfig()
{
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString filePath = dirPath + "/config.json";

    QDir dir(dirPath);
    if (!dir.exists()) {
        qDebug() << "Директория не существует, создаем:" << dirPath;
        if (!dir.mkpath(".")) { // Создаем директорию
            qWarning() << "Не удалось создать директорию:" << dirPath;
            return false;
        }
    }

    QFile file(filePath);
    if (!file.exists()) {
        qDebug() << "Файл не найден, создаем:" << filePath;
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning() << "Не удалось создать файл конфигурации по пути:" << filePath;
            return false;
        }
        return createConfig(file);
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл конфигурации для чтения:" << filePath;
        return false;
    }

    qDebug() << "Файл конфигурации успешно открыт:" << filePath;
    return true;
}

bool PresetManager::createConfig(QFile& fileToCreate)
{
    QJsonObject obj;
    obj["type"] = "";
    obj["auto-connect"] = false;
    QJsonArray params{"serial", "38400", "none"};
    obj["params"] = params;

    QJsonDocument doc(obj);

    if (fileToCreate.write(doc.toJson(QJsonDocument::Indented)) == -1) {
        qWarning() << "Не удалось записать данные в файл конфигурации";
        return false;
    }

    fileToCreate.close();
    return true;
}

