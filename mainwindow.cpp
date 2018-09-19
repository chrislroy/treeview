// modelview.cpp
#include <QDebug>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>
#include <QHeaderView>
#include <QItemDelegate>
#include <QPainter>
#include "mainwindow.h"


class MyDelegate : public QItemDelegate {
public:
    MyDelegate(QObject* parent = nullptr)
        : QItemDelegate(parent)
    {

    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        QColor groupColor("#3B4453");
        QColor itemColor("#464E61");

        QItemDelegate::paint(painter, option, index);

        auto type = index.data(Qt::UserRole + 1).toInt();
        if (!(option.state & QStyle::State_MouseOver) && type == ItemRow) {
            painter->fillRect(option.rect, itemColor);
        }
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _standardModel = new QStandardItemModel;

    QStandardItem *item = _standardModel->invisibleRootItem();
    // adding a row to the invisible root item produces a root element
    item->appendRow(createGroupRow("Quare", "", "resources/plus.png"));
    item->appendRow(createGroupRow("A very long day", "", "resources/plus.png"));
    item->appendRow(createGroupRow("Life is beautiful", "", "resources/plus.png"));
    item->appendRow(createGroupRow("Group D", "", "resources/plus.png"));

    _treeView = new MyTreeview(this);

    _treeView->setItemDelegateForColumn(2, new MyDelegate());

    connect(_treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(rowClicked(const QModelIndex &)));
    setCentralWidget(_treeView);

    _treeView->setModel(_standardModel);

    _treeView->updateColumns();
    _treeView->expandAll();
}

QList<QStandardItem *> MainWindow::createGroupRow(
    const QString &first,
    const QString &second,
    const QString &third)
{
    QColor backgroundColor("#3B4453");
    QList<QStandardItem *> rowItems;
    auto cell = new QStandardItem(first);
    cell->setEditable(false);
    rowItems << cell;
    rowItems << new QStandardItem(second);
    cell = new QStandardItem(QIcon(third), "");
    cell->setEditable(false); // make text not editable
    cell->setData(RowType::GroupRow, Qt::UserRole + 1);
    rowItems << cell;

    for(int i = 0; i < rowItems.count();++i)
        rowItems[i]->setBackground(backgroundColor);

    return rowItems;
}

void MainWindow::addItemRow(
    const QString &first,
    const QString &second,
    const QString &third,
    const QModelIndex &groupIndex)
{
    QColor backgroundColor("#464E61");

    auto item = _standardModel->item(groupIndex.row());
    auto itemRow = item->rowCount();
    item->setChild(itemRow, 0, new QStandardItem(first));
    item->setChild(itemRow, 1, new QStandardItem(second));
    auto cell = new QStandardItem(QIcon(third), "");
    cell->setEditable(false); // make text not editable
    cell->setData(RowType::ItemRow, Qt::UserRole + 1);
    item->setChild(itemRow, 2, cell);

    for (int i = 0; i < item->columnCount(); ++i)
        item->child(itemRow, i)->setBackground(backgroundColor);

}

void MainWindow::removeItemRow(const QModelIndex& index)
{
    auto parentIndex = _standardModel->parent(index);
    _standardModel->removeRow(index.row(), parentIndex);
}

void MainWindow::rowClicked(const QModelIndex &index)
{
    // demonstrate data from cell
    qDebug() << qPrintable(index.data().toString());

    if (index.column() != 2) // consider only thrid columns for now
        return;

    auto type = index.data(Qt::UserRole + 1).toInt();

    if (type == RowType::GroupRow) {
        // add a sub row
        addItemRow("111", "222", "resources/delete.png", index);
    }
    else if (type == RowType::ItemRow) {
        // delete the current row
        removeItemRow(index);
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


