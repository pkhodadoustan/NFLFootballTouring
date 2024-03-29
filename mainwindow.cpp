#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QDebug>
#include <QSortFilterProxyModel>
#include<vector>
#include <qpixmap.h>
#include "adminwindow.h"
#include "customtrip.h"
#include "tripfromcoliseum.h"
#include "tripfromfoldfield.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Info_clicked()
{
    InformationWindow* infoWin = new InformationWindow;
    infoWin->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    loginDialog* loginDlg = new loginDialog;
    this->close();
    loginDlg->show();
}

void MainWindow::on_pushButton_customTrip_2_clicked()
{
    CustomTrip* customTp = new CustomTrip;
    this->close();
    customTp->show();
}

void MainWindow::on_pushButton_customTrip_clicked()
{
    TripFromColiseum* colismTrip = new TripFromColiseum;
    this->close();
    colismTrip->show();
}
