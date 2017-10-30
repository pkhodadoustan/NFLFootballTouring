#ifndef ADDNEWSOUVENIR_H
#define ADDNEWSOUVENIR_H

#include <QDialog>
#include "database.h";

namespace Ui {
class AddNewSouvenir;
}

class AddNewSouvenir : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewSouvenir(QWidget *parent = 0);
    ~AddNewSouvenir();

private:
    Ui::AddNewSouvenir *ui;
};

#endif // ADDNEWSOUVENIR_H
