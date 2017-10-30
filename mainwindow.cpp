#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QDebug>
#include <QSortFilterProxyModel>
#include<vector>
#include <qpixmap.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    QPixmap background(":/images/Images/stadium.jpg");
//    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, background);
//    this->setPalette(palette);
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
