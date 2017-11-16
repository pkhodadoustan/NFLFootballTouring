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
    void refreshSouvList();
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void onCustomContextMenu(const QPoint &point);
    void deleteSelection();
    void deleteSouv();

    void on_backButton_clicked();

    void on_addSouvButton_clicked();

    void on_TeamCombBox_currentIndexChanged(int index);

    void on_addStadButton_clicked();

    void on_SouvView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::AdminWindow *ui;
    void refreshList();
    QSqlTableModel* tableModel;
    AdminWindow* admin;
};

#endif // ADMINWINDOW_H
