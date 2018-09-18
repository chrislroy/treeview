#pragma once

#include <QtWidgets/QMainWindow>
#include <QTreeWidget>
#include <QWidget>

QT_BEGIN_NAMESPACE // QT_BEGIN_NAMESPACE / QT_END_NAMESPACE are not needed in Qt user code
class QStandardItemModel;
class QStandardItem;
class QMouseEvent;
QT_END_NAMESPACE

enum RowType {
    GroupRow,
    ItemRow
};

class MyTreeview : public QTreeView {
    Q_OBJECT

public:
    
    MyTreeview(QWidget* = nullptr);
    void updateColumns();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    MyTreeview *_treeView;
    QStandardItemModel *_standardModel;

private:

    QList<QStandardItem *> createGroupRow(
        const QString &first,
        const QString &second,
        const QString &third);

    void addItemRow(
        const QString &first,
        const QString &second,
        const QString &third,
        const QModelIndex &parent);
    void removeItemRow(const QModelIndex& index);

public slots:
    void rowClicked(const QModelIndex &index);

public:

    MainWindow(QWidget *parent = 0);
};

