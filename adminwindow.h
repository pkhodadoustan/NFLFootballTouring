#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include <QDesktopWidget>
#include <QDebug>
#include "noteditabledelegate.h"
#include "addnewsouvenir.h"

/**
 *namespace ui
 */
namespace Ui {
class AdminWindow;
}
/**
 * @brief The AdminWindow class
 * creates a new adminwwindow
 */
class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief refreshSouvList
     * used in the admin window to refresh the souv list
     */
    void refreshSouvList();
    /**
     * @brief AdminWindow
     * @param parent
     */
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    /**
     * @brief onCustomContextMenu
     * @param point
     * used to allow the user to right click to delete
     */
    void onCustomContextMenu(const QPoint &point);

    /**
     * @brief deleteSelection
     * used to delete an elemetn in the list
     */
    void deleteSelection();

    /**
     * @brief deleteSouv
     * deletes the souvenit
     */
    void deleteSouv();

    /**
     * @brief on_backButton_clicked
     * goes back to the main window
     */
    void on_backButton_clicked();

    /**
     * @brief on_addSouvButton_clicked
     * creates new add souv window
     */
    void on_addSouvButton_clicked();

    /**
     * @brief on_TeamCombBox_currentIndexChanged
     * @param index
     * allows the user to look at different team souvenirs
     */
    void on_TeamCombBox_currentIndexChanged(int index);

    /**
     * @brief on_addStadButton_clicked
     * allows the user to add a stadium
     */
    void on_addStadButton_clicked();

    /**
     * @brief on_SouvView_customContextMenuRequested
     * @param pos
     * used to delete item
     */
    void on_SouvView_customContextMenuRequested(const QPoint &pos);

private:
    /**
     * @brief ui
     * ui ptr
     */
    Ui::AdminWindow *ui;
    /**
     * @brief refreshList
     * refreshes DB connection
     */
    void refreshList();
    /**
     * @brief tableModel
     * outputs team info
     */
    QSqlTableModel* tableModel;
    /**
     * @brief admin
     * link to admin
     */
    AdminWindow* admin;
};

#endif // ADMINWINDOW_H
