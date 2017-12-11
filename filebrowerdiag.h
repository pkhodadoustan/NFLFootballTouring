#ifndef FILEBROWERDIAG_H
#define FILEBROWERDIAG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

/**
 * namespace UI
 */
namespace Ui {
class FileBrowerDiag;
}

/**
 * @brief The FileBrowerDiag class
 * allows for a file browser
 */
class FileBrowerDiag : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowerDiag(QWidget *parent = 0);
    ~FileBrowerDiag();

private slots:
    /**
     * @brief on_folderTree_clicked
     * @param index
     * files file list on clicks
     */
    void on_folderTree_clicked(const QModelIndex &index);

    void on_fileView_clicked(const QModelIndex &index);

    void on_addBut_clicked();

    void on_add2_clicked();

private:
    void addOtherFromFile(const QModelIndex&);
    QString otherPathToFile;
    /**
     * @brief ui
     * UI ptr
     */
    Ui::FileBrowerDiag *ui;

    /**
     * @brief dirModel
     * dir model
     */
    QFileSystemModel *dirModel;

    /**
     * @brief fileModel
     * model for files
     */
    QFileSystemModel *fileModel;

    /**
     * @brief pathToFile
     * path to file
     */
    QString pathToFile;

    /**
     * @brief added
     * checs to see if item was added
     */
    bool added;

    /**
     * @brief souv
     * checks if souv was added
     */
    bool souv;
};

#endif // FILEBROWERDIAG_H
