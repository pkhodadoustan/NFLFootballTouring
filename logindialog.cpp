#include "logindialog.h"
#include "ui_logindialog.h"
#include "adminwindow.h"
#include <QDebug>
#include "mainwindow.h"
/**
 * @brief loginDialog::loginDialog
 * @param parent
 */
loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}
/**
 * @brief loginDialog::~loginDialog
 */
loginDialog::~loginDialog()
{
    delete ui;
}

/**
 * @brief loginDialog::on_loginButton_clicked
 */
void loginDialog::on_loginButton_clicked()
{
    const QString ADMIN_USERNAME = "A"; //!hardcoded username
    const QString ADMIN_PASSWORD = "A"; //!hardcoded password

        /**
         * Processing - If the username and password are correct, it will display
         *              a message box and close the current window.
         */
        if(ui->lineEdit_Username->text() == ADMIN_USERNAME && ui->lineEdit_Password->text() == ADMIN_PASSWORD)
        {

            //! If the password is correct then spawn the new AdminOptions window
            //QMessageBox::information(this, "Login", "Username and password is correct.");
            AdminWindow* admin = new AdminWindow();
            this->close();
            admin->show();
        }
        else
        {
            //! otherwise the username/password combo has failed
            QMessageBox::warning(this, "Login", "Username or Password is not correct.");
            ui->lineEdit_Username->clear();
            ui->lineEdit_Password->clear();
        }

}

/**
 * @brief loginDialog::on_pushButton_clicked
 */
void loginDialog::on_pushButton_clicked()
{
    MainWindow* main = new MainWindow;
    this->close();
    main->show();
}
