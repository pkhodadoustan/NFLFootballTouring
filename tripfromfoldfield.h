#ifndef TRIPFROMFOLDFIELD_H
#define TRIPFROMFOLDFIELD_H

#include <QDialog>

namespace Ui {
class TripFromFoldfield;
}

class TripFromFoldfield : public QDialog
{
    Q_OBJECT

public:
    explicit TripFromFoldfield(QWidget *parent = 0);
    ~TripFromFoldfield();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TripFromFoldfield *ui;

    QVector<QString> souvenirName;
    QVector<double>  souvenirPrice;
    QVector<int>  souvenirQuantity;
};

#endif // TRIPFROMFOLDFIELD_H
