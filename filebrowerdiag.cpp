#include "filebrowerdiag.h"
#include "ui_filebrowerdiag.h"

FileBrowerDiag::FileBrowerDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBrowerDiag)
{
    ui->setupUi(this);

    //used to check if file has been added
    added = false;
    souv = false;

    //hides add button and fileTable
//    ui->addButt->hide();
//    ui->fileTable->hide();
//    ui->SouvTab->hide();

    //sets up paths for the folder Trees
    QString sPath = "";
    dirModel  = new QFileSystemModel(this);
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
