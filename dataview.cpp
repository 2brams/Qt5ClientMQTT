#include "dataview.h"
#include "ui_dataview.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QTimer>
#include <QRandomGenerator>

DataView::DataView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataView)
{
    ui->setupUi(this);
    dataTimer = new QTimer;


    ui->customPlot->setBackground(QBrush(QColor( 224, 224, 224)));
    ui->customPlot->legend->setVisible(true);

    ui->customPlot->addGraph();
    QPen pen0;
    pen0.setWidth(2);
    pen0.setColor(QColor("green"));
    ui->customPlot->graph(0)->setName("température");
    ui->customPlot->graph(0)->setPen(pen0);

    ui->customPlot->addGraph();
    QPen pen1;
    pen1.setStyle(Qt::DotLine);
    pen1.setWidth(2);
    pen1.setColor(QColor("blue"));
    ui->customPlot->graph(1)->setName("humidité");
    ui->customPlot->graph(1)->setPen(pen1);

    tmpG=0.0;
    humG=0.0;
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(5, 50);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect( ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),  ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect( ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),  ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    connect(dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer->setInterval(1000);
    dataTimer->start();

    connect(parent, SIGNAL(sendData(QString)), this, SLOT(receveData(QString)));

}

DataView::~DataView()
{
    delete ui;
}

void DataView::receveData(QString msg)
{
    QString val= QString(msg);
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();

    QJsonValue tmp = sett2.value(QString("temperature"));
    QJsonValue hum = sett2.value(QString("humidity"));

    tmpG= tmp.toDouble();
    ui->label_tmp->setText(QString::number(tmp.toDouble(),'g',3));
    humG = hum.toDouble();
    ui->label_hum->setText(QString::number(hum.toDouble(),'g',3));


}

void DataView::realtimeDataSlot()
{
    static QTime time(QTime::currentTime());
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds

    static double lastPointKey = 0;
    if (key - lastPointKey > 0.002) // at most add point every 2 ms
    {
        // add data to lines:
        //        ui->customPlot->graph(0)->addData(key, QRandomGenerator::global()->bounded(tmpG));
        //        ui->customPlot->graph(1)->addData(key, QRandomGenerator::global()->bounded(humG));
        ui->customPlot->graph(0)->addData(key, tmpG);
        ui->customPlot->graph(1)->addData(key,humG);

        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->customPlot->replot();

    ui->label->setText( QString("Total Data points: %1").arg(ui->customPlot->graph(0)->data()->size()));

}

