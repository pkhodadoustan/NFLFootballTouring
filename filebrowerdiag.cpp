#include "filebrowerdiag.h"
#include "ui_filebrowerdiag.h"
#include "database.h"

FileBrowerDiag::FileBrowerDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBrowerDiag)
{
    ui->setupUi(this);

    //used to check if file has been added
    added = false;
    souv = false;

    //hides add button and fileTable
    ui->addBut->hide();
    ui->fileTable->hide();
    ui->souvTable->hide();
    ui->add2->hide();
    //sets up paths for the folder Trees
    QString sPath = "";
    dirModel = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);
    ui->folderTree->setModel(dirModel);
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(sPath);
    ui->fileView->setModel(fileModel);

    ui->folderTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

FileBrowerDiag::~FileBrowerDiag()
{
    delete ui;
}

void FileBrowerDiag::on_folderTree_clicked(const QModelIndex &index)
{
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->fileView->setRootIndex(fileModel->setRootPath(sPath));
}

void FileBrowerDiag::on_fileView_clicked(const QModelIndex &index)
{
    //clear errorLabel
    ui->errorLabel->clear();

    if (souv == true)
        addOtherFromFile(index);

    //sets up tableWidget
    ui->fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->fileTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->fileTable->setColumnCount(3);
    QStringList headers;
    headers << "Start" << "End" << "Distance";
    ui->fileTable->setHorizontalHeaderLabels(headers);

    Database* db = Database::getInstance(); //db instance
    //sets path
    QString path = fileModel->fileInfo(index).absoluteFilePath();
    pathToFile = path;
    bool correctFileType = path.endsWith(".csv");
    qDebug() << path;
    //checks if file is correct
    if (!correctFileType)
        ui->errorLabel->setText("Please select a .csv file");
    else {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        }
        else {
            qDebug() << "OPen file";

            //reads file and outsputs info to Table
            while (!file.atEnd())
            {
                QString test = QString(file.readLine());
                QStringList toAdd = db->parseCSVFile(test);

                QTableWidgetItem *start = new QTableWidgetItem(toAdd.at(0));
                QTableWidgetItem *end = new QTableWidgetItem(toAdd.at(1));
                QTableWidgetItem *dist = new QTableWidgetItem(toAdd.at(2));
                ui->fileTable->insertRow(ui->fileTable->rowCount());
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 0, start);
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 1, end);
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 2, dist);

                ui->fileTable->show();
                ui->errorLabel->setText("This is the information from the file. Select a Souvenir file or click ADD");
            }
            ui->addBut->show();
            souv = true;
        }

        ui->errorLabel->setText("select an associated team file");


    }
}

void FileBrowerDiag::on_addBut_clicked()
{
    //parses and added file contents if not yet added
    if (!added)
    {
        Database* db = Database::getInstance(); //db instance

        //checks if file can open
        QFile file(pathToFile);
        if (!file.open(QIODevice::ReadOnly))
            qDebug() << file.errorString();
        else {
            qDebug() << "File is open";

            //reads each line of the file and parses the contents to DB
            while (!file.atEnd())
            {
                QString test = QString(file.readLine());
                QStringList toAdd = db->parseCSVFile(test);
                db->addNewDistance(toAdd);
            }

            //confirmation message
            ui->errorLabel->setText("select an associated team file");
            added = true;
            ui->add2->show();
            ui->addBut->hide();
        }
    }
}

void FileBrowerDiag::addOtherFromFile(const QModelIndex &index) {
    Database* db = Database::getInstance();

    //sets up tableWidget
    ui->souvTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->souvTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->souvTable->setColumnCount(8);
    QStringList headers2;
    headers2 << "Team_Name" << "Stadium_Name" << "Seating_Capacity" << "Location" << "Conference" << "Surface_Type" << "Stadium_Roof_Type" << "Star_Player";
    ui->souvTable->setHorizontalHeaderLabels(headers2);
    QString path = fileModel->fileInfo(index).absoluteFilePath();

    otherPathToFile = fileModel->fileInfo(index).absoluteFilePath();
    bool correctFileType = path.endsWith(".csv");
    qDebug() << otherPathToFile;
    //checks if file is correct
    if (!correctFileType)
        ui->errorLabel->setText("Please select a .csv file");
    else {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        }
        else {
            qDebug() << "OPen file";
            otherPathToFile = path;
            //reads file and outsputs info to Table
            while (!file.atEnd())
            {
                QString test = QString(file.readLine());
                QStringList toAdd = db->parseCSVFile(test);

                QTableWidgetItem *T = new QTableWidgetItem(toAdd.at(0));
                QTableWidgetItem *S= new QTableWidgetItem(toAdd.at(1));
                QTableWidgetItem *SC = new QTableWidgetItem(toAdd.at(2));
                QTableWidgetItem *L = new QTableWidgetItem(toAdd.at(3));
                QTableWidgetItem *C = new QTableWidgetItem(toAdd.at(4));
                QTableWidgetItem *ST = new QTableWidgetItem(toAdd.at(5));
                QTableWidgetItem *SRT = new QTableWidgetItem(toAdd.at(6));
                QTableWidgetItem *SP = new QTableWidgetItem(toAdd.at(7));


                ui->souvTable->insertRow(ui->souvTable->rowCount());
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 0, T);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 1, S);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 2, SC);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 3, L);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 4, C);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 5, ST);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 6, SRT);
                ui->souvTable->setItem(ui->souvTable->rowCount() - 1, 7, SP);
                ui->souvTable->show();
                ui->errorLabel->setText("This is the information from the file. click ADD");
            }
        }
    }
    added = false;
}

void FileBrowerDiag::on_add2_clicked()
{
    //parses and added file contents if not yet added
    if (!added)
    {
        Database* db = Database::getInstance(); //db instance

        //checks if file can open
        QFile file(otherPathToFile);
        if (!file.open(QIODevice::ReadOnly))
            qDebug() << file.errorString();
        else {
            qDebug() << "File is open";

            //reads each line of the file and parses the contents to DB
            while (!file.atEnd())
            {
                QString test = QString(file.readLine());
                QStringList toAdd = db->parseCSVFile(test);
                db->addNewTeam(toAdd);

            }

            //confirmation message
            ui->errorLabel->setText("New stadiums added to database");
            added = true;
        }
    }
}

//void FileBrowerDiag::on_fileView_clicked(const QModelIndex &index)
//{

//}

//void FileBrowerDiag::on_addBut_clicked()
//{

//}

//void FileBrowerDiag::on_add2_clicked()
//{

//}
