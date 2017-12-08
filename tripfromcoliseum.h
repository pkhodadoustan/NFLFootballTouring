#ifndef TRIPFROMCOLISEUM_H
#define TRIPFROMCOLISEUM_H

#include <QDialog>

namespace Ui {
class TripFromColiseum;
}

class TripFromColiseum : public QDialog
{
    Q_OBJECT

public:
    explicit TripFromColiseum(QWidget *parent = 0);
    ~TripFromColiseum();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TripFromColiseum *ui;

    QVector<QString> souvenirName;
    QVector<double>  souvenirPrice;
    QVector<int>  souvenirQuantity;
};

#endif // TRIPFROMCOLISEUM_H
