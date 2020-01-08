#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QMqttClient(this);
    client->setHostname("10.0.4.203");
    client->setPort(1883);

    connect(client, SIGNAL(connected()), this, SLOT(connecte()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(messageRecu(const QByteArray &, const QMqttTopicName &)));

    client->connectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
    client->disconnectFromHost();
}

void MainWindow::connecte()
{
    subscription = client->subscribe(QLatin1String("test"));
    if (!subscription)
    {
        QMessageBox::critical(this, "Erreur", "Impossible de s'abonner au broker!");
        return;
    }
}

void MainWindow::deconnecte()
{
    //    QMessageBox::critical(this, "Information", "Déconnexion du broker");
    qDebug() << "Information", "Déconnexion du broker";
}

void MainWindow::messageRecu(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << QDateTime::currentDateTime().toString() << topic.name() << message;
    QString val= QString(message);
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    //qDebug() << sett2;
    QJsonValue tmp = sett2.value(QString("temperature"));
    QJsonValue hum = sett2.value(QString("humidity"));

    qDebug() << tmp.toDouble();
    qDebug() << hum.toDouble();

}

