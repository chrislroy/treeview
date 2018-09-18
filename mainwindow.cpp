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
    auto cell = new QStandardItem(first);
    cell->setEditable(false);
    rowItems << cell;
    rowItems << new QStandardItem(second);
    cell = new QStandardItem(QIcon(third), "");
    cell->setEditable(false); // make text not editable
    cell->setData(rowType);
    rowItems << cell;

    return rowItems;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _standardModel = new QStandardItemModel;

    QStandardItem *item = _standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(prepareRow(RowType::GroupRow, "Quare", "", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "A very long day", "", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "Life is beautiful", "", "resources/plus.png"));
    item->appendRow(prepareRow(RowType::GroupRow, "Group D", "", "resources/plus.png"));

    _treeView = new MyTreeview(this);
    _treeView->setObjectName("brapbrapbrap");

    connect(_treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(rowClicked(const QModelIndex &)));
    setCentralWidget(_treeView);

    _treeView->setModel(_standardModel);

    _treeView->updateColumns();
    _treeView->expandAll();
}

void MainWindow::rowClicked(const QModelIndex &index)
{
    qDebug() << index;

    if (index.column() != 2) // consider only thrid columns for now
        return;
    auto type = index.data(257).toInt();
    qDebug() << "Type: " << type;

    if (type == RowType::GroupRow) {
        // add a sub row
        qDebug() << "adding row!!!";

        _standardModel->insertRow(index.row() + 1, prepareRow(RowType::ItemRow, "111", "222", "resources/delete.png"));
    }
    else if (type == RowType::ItemRow) {

        // delete the current row
        _standardModel->removeRow(index.row());
    }

}

MyTreeview::MyTreeview(QWidget* parent)
    : QTreeView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMinimumWidth(300);
}

void MyTreeview::updateColumns()
{
    // header()->setCascadingSectionResizes(false);
    header()->setSectionResizeMode(0, QHeaderView::Stretch);
    header()->setSectionResizeMode(1, QHeaderView::Stretch);
    header()->setSectionResizeMode(2, QHeaderView::Fixed);
    header()->setStretchLastSection(false);
    header()->resizeSection(2, 50);
}


