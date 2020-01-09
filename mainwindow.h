#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QtMqtt/QtMqtt>
#include <QLabel>
#include "dataview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    QString sendData(QString);

public slots:
    void connecte();
    void connexion();
    void souscrire();
    void deconnecte();
    void messageRecu(const QByteArray &message, const QMqttTopicName &topic);
    void setHost(QString);
    void setPort(int);

private:
    Ui::MainWindow *ui;
    QMqttClient *client;
    QMqttSubscription *subscription;
    DataView *dataPage;
    QLabel *iconLbl;
};
#endif // MAINWINDOW_H
