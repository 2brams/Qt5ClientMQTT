#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class DataView;
}

class DataView : public QDialog
{
    Q_OBJECT

public:
    explicit DataView(QWidget *parent = nullptr);
    ~DataView();


private slots:
    void receveData(QString);
    void realtimeDataSlot();

private:
    Ui::DataView *ui;
    QTimer  *dataTimer;
    double tmpG;
    double humG;
};

#endif // DATAVIEW_H
