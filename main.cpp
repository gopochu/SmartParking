#include "mainwindow.h"
#include "mqtt.h"
#include <QDebug>
#include <QApplication>
#include <QUuid>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 600);
    w.setWindowTitle("Smart parking");
    w.show();

    // Инициализация клиента MQTT
    qDebug() << "Initializing MQTT client...";
    QMqttClient *client = setupMqttClient("r11ad39.ala.eu-central-1.emqxsl.com", 8084, QUuid::createUuid().toString(), "vadlap", "12345");

    if (!client) {
        qDebug() << "Failed to create MQTT client.";
        return -1;
    }

    // Публикация данных
    publishSensorData(client);
    return a.exec();
}
