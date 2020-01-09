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
    dataPage = new DataView(this);
    client->setHostname(ui->lineEdit_host->text());
    client->setPort(ui->spinBox_port->value());

    ui->label->setPixmap(QPixmap(":/logo.png").scaledToHeight(100));


    iconLbl = new QLabel;

    iconLbl->setPixmap(QPixmap(":/disconnected.png").scaledToHeight((ui->statusbar->height()/2)+10));
    iconLbl->setScaledContents(false);
    iconLbl->setAlignment(Qt::AlignRight);

    ui->statusbar->showMessage("Déconnecter");
    ui->statusbar->insertPermanentWidget(0,iconLbl,0);



    connect(ui->pushButton_conect, SIGNAL(clicked()), this, SLOT(connexion()));
    connect(ui->pushButton_souscrire, SIGNAL(clicked()), this, SLOT(souscrire()));
    connect(ui->pushButton_quitter, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->lineEdit_host, SIGNAL(textEdited(QString)), this, SLOT(setHost(QString)));
    connect(ui->spinBox_port, SIGNAL(valueChanged(int)), this, SLOT(setPort(int)));



    connect(client, SIGNAL(connected()), this, SLOT(connecte()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(client, SIGNAL(messageReceived(const QByteArray &, const QMqttTopicName &)), this, SLOT(messageRecu(const QByteArray &, const QMqttTopicName &)));

}

MainWindow::~MainWindow()
{
    delete ui;
    client->disconnectFromHost();
}

void MainWindow::connecte()
{
    ui->statusbar->showMessage("Connecter");
    iconLbl->setPixmap(QPixmap(":/connected.png").scaledToHeight((ui->statusbar->height()/2)+10));
}

void MainWindow::deconnecte()
{
    ui->statusbar->showMessage("Déconnecter");
    iconLbl->setPixmap(QPixmap(":/disconnected.png").scaledToHeight((ui->statusbar->height()/2)+10));
}

void MainWindow::connexion()
{
    if (client->state() == QMqttClient::Disconnected) {
        ui->lineEdit_host->setEnabled(false);
        ui->spinBox_port->setEnabled(false);
        ui->pushButton_conect->setText(tr("Déconnexion"));
        client->connectToHost();
    } else {
        ui->lineEdit_host->setEnabled(true);
        ui->spinBox_port->setEnabled(true);
        ui->pushButton_conect->setText(tr("Connexion"));
        client->disconnectFromHost();
    }
}

void MainWindow::souscrire()
{

    subscription = client->subscribe(ui->lineEdit_topic->text());
    if (!subscription)
    {
        const QString content =  QLatin1String(" Impossible de s'abonner au broker! ")
                + QLatin1Char('\n')
                + QLatin1String(" verifier que vous n'etes pas deconnecter. ")
                + QLatin1Char('\n');
        QMessageBox::critical(this, "Erreur", content);
        return;
    } else {
        hide();
        dataPage->exec();
        show();

    }
}



void MainWindow::messageRecu(const QByteArray &message, const QMqttTopicName &topic)
{
    emit sendData(message);

}

void MainWindow::setHost(QString text)
{
    client->setHostname(text);
}

void MainWindow::setPort(int value)
{
    client->setPort(value);
}

