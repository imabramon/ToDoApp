#include <QDir>
#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "datastorer.h"
#include "task.h"

namespace DSPrivate {
    QString formDataFilePath();
    void createDataPath();

    QJsonObject convertTaskToJsonObject(Task &Task);
    Task convertJsonObjectToTask(QJsonObject &jsonObject);
};

QString DSPrivate::formDataFilePath() {
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    return dataDir.absoluteFilePath(QStringLiteral("data.json"));
}

void DSPrivate::createDataPath() {
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir directoryCreator;
    directoryCreator.mkpath(path);
}

Task DSPrivate::convertJsonObjectToTask(QJsonObject &jsonObject) {
    return Task(
                0,
        jsonObject["name"].toString(),
        jsonObject["category"].toString(),
        jsonObject["isdone"].toBool()
    );
}

QJsonObject DSPrivate::convertTaskToJsonObject(Task &Task) {
    QJsonObject TaskObject;
    TaskObject["name"] = Task.name;
    TaskObject["category"]= Task.category;
    TaskObject["isdone"] = Task.isDone;
    return TaskObject;
}

QList<Task> DataStorer::readData() {
    QList<Task> Tasks;
    qDebug() << "Data file path: " << DSPrivate::formDataFilePath();
    QFile dataFile(DSPrivate::formDataFilePath());
    if(!dataFile.exists()) {
        // Data does not exists
        return Tasks;
    }
    if(!dataFile.open(QFile::ReadOnly)) {
        // File could not be openned
        return Tasks;
    }
    auto rawData = dataFile.readAll();
    auto jsonDocument = QJsonDocument::fromJson(rawData);
    if(jsonDocument.isNull()) {
        // Data was not parsed
        return Tasks;
    }
    if(!jsonDocument.isArray()) {
        // Root element is not array
        return Tasks;
    }
    auto jsonArray = jsonDocument.array();
    foreach(QJsonValue arrayValue, jsonArray) {
        if(!arrayValue.isObject()) continue; // Element of the array is not an object
        auto jsonObject = arrayValue.toObject();
        Tasks.append(DSPrivate::convertJsonObjectToTask(jsonObject));
    }
    return Tasks;
}

void DataStorer::storeData(QList<Task> &Tasks) {
    QJsonArray jsonArray;
    foreach(Task Task, Tasks) {
        jsonArray.append(DSPrivate::convertTaskToJsonObject(Task));
    }
    QJsonDocument jsonDocument;
    jsonDocument.setArray(jsonArray);
    DSPrivate::createDataPath();
    QFile dataFile(DSPrivate::formDataFilePath());
    dataFile.open(QFile::WriteOnly);
    dataFile.write(jsonDocument.toJson(QJsonDocument::Indented));
    dataFile.close();
}

