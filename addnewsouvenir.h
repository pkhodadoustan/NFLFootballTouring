#ifndef ADDNEWSOUVENIR_H
#define ADDNEWSOUVENIR_H

#include <QDialog>
#include "database.h"
#include "adminwindow.h"
/**
 * namespace U
 */
namespace Ui {
class AddNewSouvenir;
}

/**
 * @brief The AddNewSouvenir class
 * allows an admin to add a new souvanir to a team
 */
class AddNewSouvenir : public QDialog
{
    Q_OBJECT
public:
    /**
     * @brief AddNewSouvenir
     * @param parent
     * constructor for the class
     */
    explicit AddNewSouvenir(QWidget *parent = 0);

    ~AddNewSouvenir();
private slots:
    /**
     * @brief on_addButton_clicked
     * adds the new sounvinir to the team
     */
    void on_addButton_clicked();

private:
    Ui::AddNewSouvenir *ui;
};

#endif // ADDNEWSOUVENIR_H
