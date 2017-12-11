#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>

/**
 * purchase souvenirs
 */
namespace Ui {
class PurchaseSouvenirs;
}

class PurchaseSouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseSouvenirs(QWidget *parent = 0);
    ~PurchaseSouvenirs();

private:
    Ui::PurchaseSouvenirs *ui;
};

#endif // PURCHASESOUVENIRS_H
