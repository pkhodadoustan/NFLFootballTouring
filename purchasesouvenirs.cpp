#include "purchasesouvenirs.h"
#include "ui_purchasesouvenirs.h"

PurchaseSouvenirs::PurchaseSouvenirs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseSouvenirs)
{
    ui->setupUi(this);
}

PurchaseSouvenirs::~PurchaseSouvenirs()
{
    delete ui;
}

