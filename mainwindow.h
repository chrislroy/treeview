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
    //void mouseReleaseEvent(QMouseEvent *);

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    MyTreeview *treeView;
    QStandardItemModel *standardModel;

public slots:
    void rowClicked(const QModelIndex &index);

public:



    MainWindow(QWidget *parent = 0);
};

