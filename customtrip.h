#ifndef CUSTOMTRIP_H
#define CUSTOMTRIP_H

#include <QDialog>

namespace Ui {
class CustomTrip;
}

class CustomTrip : public QDialog
{
    Q_OBJECT

public:
    explicit CustomTrip(QWidget *parent = 0);
    ~CustomTrip();

private slots:
    void on_pushButton_back_clicked();

    void on_comboBox_stadiums_currentIndexChanged(int index);

private:
    Ui::CustomTrip *ui;

    QVector<QString> souvenirName;
    QVector<double>  souvenirPrice;
    QVector<int>  souvenirQuantity;
};

#endif // CUSTOMTRIP_H
