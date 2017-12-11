#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "adminwindow.h"
#include <QMessageBox>

/**
 *class login
 */
namespace Ui {
class loginDialog;
}

/**
 * @brief The loginDialog class
 * allows the admin to login
 */
class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

private slots:
    /**
     * @brief on_loginButton_clicked
     * verified credentials
     */
    void on_loginButton_clicked();

    /**
     * @brief on_pushButton_clicked
     * back button to main wind
     */
    void on_pushButton_clicked();

private:
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
