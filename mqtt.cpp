#include "mqtt.h"
#include <QDebug>
#include <QDateTime>
#include <QSslConfiguration>
#include <QMqttTopicName>
#include <QSslCertificate>
#include <QFile>

QMqttClient* setupMqttClient(const QString& hostname, quint16 port, const QString& clientID, const QString& username, const QString& password) {
    // Создаем экземпляр QMqttClient
    QMqttClient *client = new QMqttClient();

    // Устанавливаем адрес и порт сервера
    client->setHostname(hostname);
    client->setPort(port);
    client->setClientId(clientID);
    client->setUsername(username);
    client->setPassword(password);

    // Включаем SSL
    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    QFile certFile("emqxsl-ca.crt"); // путь к сертификату
    if (certFile.open(QIODevice::ReadOnly)) {
        QSslCertificate cert(&certFile, QSsl::Pem);
        sslConfig.setCaCertificates({ cert });
        certFile.close();
    } else {
        qDebug() << "Не удалось открыть файл сертификата!";
    }

    client->connectToHostEncrypted(sslConfig);

    // Подключаемся к сигналам для отладки
    QObject::connect(client, &QMqttClient::connected, []() {
        qDebug() << "Connected to MQTT server";
    });

    QObject::connect(client, &QMqttClient::disconnected, []() {
        qDebug() << "Disconnected from MQTT server";
    });

    QObject::connect(client, &QMqttClient::stateChanged, [](QMqttClient::ClientState state) {
        qDebug() << "MQTT Client State Changed:" << state;
    });

    return client;
}

void publishSensorData(QMqttClient *client) {
    if (!client || client->state() != QMqttClient::Connected) {
        qDebug() << "Client is not connected!";
        return;
    }

    // Создаем JSON-объект для отправки данных
    QJsonObject sensorData;
    sensorData["slot_id"] = 1;
    sensorData["occupied"] = false;
    sensorData["timestamp"] = QDateTime::currentSecsSinceEpoch();

    QJsonDocument doc(sensorData);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);

    // Публикуем данные с использованием QMqttTopicName
    QMqttTopicName topic("/mqtt/parking/sensor_data");
    auto result = client->publish(topic, payload);
    if (result == -1) {
        qDebug() << "Failed to publish message.";
    } else {
        qDebug() << "Message published with QoS 0, message ID:" << result;
    }
}
