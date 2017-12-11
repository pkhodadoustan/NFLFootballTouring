#ifndef NOTEDITABLEDELEGATE_H
#define NOTEDITABLEDELEGATE_H


#include <QItemDelegate>

/**
 * @brief The NotEditableDelegate class
 * for delete in adminwindow
 */
class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate(QObject *parent = 0)
        : QItemDelegate(parent)
    {}

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    { return false; }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    { return Q_NULLPTR; }

};
#endif // NOTEDITABLEDELEGATE_H
