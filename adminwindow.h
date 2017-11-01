#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDesktopWidget>
#include <QDebug>
#include "noteditabledelegate.h"
#include "addnewsouvenir.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void onCustomContextMenu(const QPoint &point);
    void deleteSelection();

    void on_backButton_clicked();

    void on_addSouvButton_clicked();

    void on_TeamCombBox_currentIndexChanged(int index);

    void on_addStadButton_clicked();

private:
    Ui::AdminWindow *ui;
    void refreshList();
    QSqlTableModel* tableModel;

};

#endif // ADMINWINDOW_H
