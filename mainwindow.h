#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QtMqtt/QtMqtt>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void connecte();
    void deconnecte();
    void messageRecu(const QByteArray &message, const QMqttTopicName &topic);

private:
    Ui::MainWindow *ui;
    QMqttClient *client;
    QMqttSubscription *subscription;
};
#endif // MAINWINDOW_H
