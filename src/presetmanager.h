#ifndef PRESETMANAGER_H
#define PRESETMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

class PresetManager
{
public:
    PresetManager();
    static PresetManager& Instance();
    bool openConfig();
    bool createConfig(QFile &fileToCreate);
};

#endif // PRESETMANAGER_H
