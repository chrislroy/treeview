// modelview.cpp
#include <QDebug>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>
#include <QHeaderView>
#include "mainwindow.h"

QList<QStandardItem *> prepareRow(
    RowType rowType,
    const QString &first,
    const QString &second,
    const QString &third)
{
    QList<QStandardItem *> rowItems;
    rowItems << new QStandardItem(first);
    rowItems << new QStandardItem(second);
    auto item = new QStandardItem(QIcon(third), "");
    item->setData(rowType);
    rowItems << item;

    return rowItems;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    treeView = new MyTreeview(this);

    connect(treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(rowClicked(const QModelIndex &)));
    setCentralWidget(treeView);
    standardModel = new QStandardItemModel;

    QStandardItem *item = standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(prepareRow(RowType::GroupRow, "Group A", "Quare", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "Group B", "Triangle", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "Group C", "Circle", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "Group D", "Weird", "resources/plus.png"));

    treeView->setModel(standardModel);
    treeView->expandAll();
}

void MainWindow::rowClicked(const QModelIndex &index)
{
    qDebug() << index;

    if (index.column() != 2) // consider only thrid columns for now
        return;
    auto type = index.data().toInt();
    qDebug() << "Type: " << type;

    if (type == RowType::GroupRow) {
        // add a sub row
        qDebug() << "adding row!!!";
        auto model = dynamic_cast<const QStandardItemModel*>(index.model());
        QStandardItem *section = model->item(index.row());
        section->appendRow(prepareRow(RowType::ItemRow, "111", "222", "resources/delete.png"));
        
    }
    else if (index.data() == RowType::ItemRow) {
        // delete the current row
    }

}

MyTreeview::MyTreeview(QWidget* parent)
    : QTreeView(parent)
{
}


//void MyTreeview::mouseReleaseEvent(QMouseEvent *ev)
//{
//    qDebug() << ev->pos();
//    QTreeView::mouseReleaseEvent(ev);
//    QModelIndex index = QTreeView::indexAt(ev->pos());
//    if (index.column() != 2) // consider only thrid columns for now
//        return;
//    auto type = index.data().toInt();
//    if (isExpanded(index))
//        qDebug() << "Index expanded";
//
//    if (type == RowType::GroupRow) {
//        // add a sub row
//        qDebug() << "adding row!!!";
//        auto model = dynamic_cast<const QStandardItemModel*>(index.model());
//        QStandardItem *section = model->item(index.row());
//        section->appendRow(prepareRow(RowType::ItemRow, "111", "222", "resources/delete.png"));
//
//    }
//    else if (index.data() == RowType::ItemRow) {
//        // delete the current row
//    }
//
//}


