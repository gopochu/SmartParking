#ifndef MQTT_H
#define MQTT_H

#include <QMqttClient>
#include <QJsonObject>
#include <QJsonDocument>

QMqttClient* setupMqttClient(const QString& hostname, quint16 port, const QString& clientID, const QString& username, const QString& password);
void publishSensorData(QMqttClient *client);

#endif // MQTT_H
