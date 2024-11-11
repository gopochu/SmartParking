#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &MainWindow::generateRandomNumber);
    timer->start(10000);
}

MainWindow::~MainWindow(){
    delete ui;
}

//Кнопка
void MainWindow::on_pushButton_clicked(){
    ui->label_4->show();
    ui->label_8->show();
    ui->label_3->show();
    ui->label_9->show();
}

void MainWindow::on_pushButton_2_clicked(){
    ui->label_4->hide();
    ui->label_8->hide();
    ui->label_3->hide();
    ui->label_9->hide();
}

void MainWindow::on_pushButton_3_clicked(){
    ui->checkBox_2->show();
    ui->checkBox->show();
    ui->label_5->show();
    isAuto = false;
}

void MainWindow::on_pushButton_4_clicked(){
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->label_5->hide();
    isAuto = true;
}

void MainWindow::on_checkBox_stateChanged(int state){
    if (state == Qt::Checked) {
        ui->checkBox->setText("Шлакбаум открыт");
    } else {
        ui->checkBox->setText("Шлакбаум закрыт");
    }
}

void MainWindow::on_checkBox_2_stateChanged(int state){
    if (state == Qt::Checked) {
        ui->checkBox_2->setText("Табло включено");
    } else {
        ui->checkBox_2->setText("Табло выключено");
    }
}

void MainWindow::generateRandomNumber(){
    // Генерируем случайное число от 40 до 60
    int randomNumber = QRandomGenerator::global()->bounded(50, 63);  // 63 не включительно
    // if(randomNumber > 61 && isAuto){ ui->label_6->show(); }
    // else if(randomNumber < 62 || isAuto == false) { ui->label_6->hide(); }
    // Выводим это число в label
    ui->label_8->setText(QString::number(62-randomNumber));
    ui->label_9->setText(QString::number(randomNumber));
}
