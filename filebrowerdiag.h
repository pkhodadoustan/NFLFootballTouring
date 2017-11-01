#ifndef FILEBROWERDIAG_H
#define FILEBROWERDIAG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
namespace Ui {
class FileBrowerDiag;
}

class FileBrowerDiag : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowerDiag(QWidget *parent = 0);
    ~FileBrowerDiag();

private slots:
    void on_folderTree_clicked(const QModelIndex &index);

private:
    Ui::FileBrowerDiag *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QString pathToFile;
    bool added;
    bool souv;
};

#endif // FILEBROWERDIAG_H
