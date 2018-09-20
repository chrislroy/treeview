// modelview.cpp
#include <QDebug>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMouseEvent>
#include <QHeaderView>
#include <QItemDelegate>
#include <QPainter>
#include <QList>
#include "mainwindow.h"

class MyDelegate : public QItemDelegate {
public:
    MyDelegate(QObject* parent = nullptr)
        : QItemDelegate(parent)
    {

    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

        auto type = index.data(Qt::UserRole + 1).toInt();

        if (type == ItemRow) {
            QColor itemColor("#464E61");
            if (!(option.state & QStyle::State_MouseOver)) {
                painter->fillRect(option.rect, itemColor);
            }
            else
                QItemDelegate::paint(painter, option, index);
        }
        else {
            QItemDelegate::paint(painter, option, index);
        }
    }

    //void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    //    auto type = index.data(Qt::UserRole + 1).toInt();
    //    if (type == ItemRow) {
    //        QColor itemColor("#464E61");
    //        if (option.state & QStyle::State_MouseOver || option.state & QStyle::State_Selected) {
    //            painter->fillRect(option.rect, itemColor);
    //        }
    //        else {
    //            QItemDelegate::drawBackground(painter, option, index);
    //        }
    //    }
    //    else {
    //        QItemDelegate::drawBackground(painter, option, index);
    //    }
    //}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_standardModel = new QStandardItemModel;

    m_rootItem = m_standardModel->invisibleRootItem();
    m_rootIndex = m_rootItem->index();

    QList<ModelData> data = {
        ModelData(RowType::GroupRow, "Quare", ""),
        ModelData(RowType::ItemRow, "Item1", "aaa"),
        ModelData(RowType::ItemRow, "Item2", "bbb"),
        ModelData(RowType::ItemRow, "Imte3", "ccc"),
        ModelData(RowType::GroupRow, "A very long day", ""),
        ModelData(RowType::GroupRow, "Life is beautiful", ""),
        ModelData(RowType::GroupRow, "Group D", ""),
        ModelData(RowType::ItemRow, "Item1", "aaa"),
        ModelData(RowType::ItemRow, "Item2", "bbb"),
        ModelData(RowType::ItemRow, "Imte3", "ccc")
    };

    initializeModel(data);

    m_treeView = new MyTreeview(this);

    m_treeView->setItemDelegateForColumn(2, new MyDelegate());

    connect(m_treeView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(rowClicked(const QModelIndex &)));
    setCentralWidget(m_treeView);

    m_treeView->setModel(m_standardModel);

    m_treeView->updateColumns();
    m_treeView->expandAll();
}

ModelData::ModelData(int type, const QString& label1, const QString& label2)
    : m_type(type)
    , m_label1(label1)
    , m_label2(label2)
{

}
void MainWindow::initializeModel(const QList<ModelData> &dataList)
{
    auto index = m_rootIndex;
    int groupIndex = -1;
    Q_ASSERT_X(dataList[0].type() == RowType::GroupRow, "initializeModel", "First Item must be a RowType::GroupRow");
    for (auto data : dataList) {
        if (data.type() == RowType::GroupRow) {
            index = m_rootIndex;
            groupIndex++;
        }
        else {
            index = m_standardModel->item(groupIndex, 0)->index();
        }
        addItemRow(data.label1(), data.label2(), index);
    }
}

void MainWindow::fetchModel(QList<ModelData> &data)
{
    // clear data
    data = {};
    // TODO - to be completed

}

void MainWindow::addItemRow(
    const QString &first,
    const QString &second,
    const QModelIndex &index)
{   
    auto isGroup = index == m_rootIndex;
    int type = isGroup ? RowType::GroupRow : RowType::ItemRow;  ;
    QColor backgroundColor = isGroup ? QColor("#3B4453") : QColor("#464E61");
    QStandardItem *item = isGroup ? m_rootItem : m_standardModel->item(index.row());

    auto itemRow = item->rowCount();
    item->setChild(itemRow, 0, new QStandardItem(first));
    item->setChild(itemRow, 1, new QStandardItem(second));
    auto buttonCell = isGroup ? new QStandardItem(QIcon("resources/plus.png"), "") : new QStandardItem(QIcon("resources/delete.png"), "");
    buttonCell->setEditable(false);
    buttonCell->setData(type, Qt::UserRole + 1);
    item->setChild(itemRow, 2, buttonCell);

    for (int i = 0; i < item->columnCount(); ++i)
        item->child(itemRow, i)->setBackground(backgroundColor);
}

void MainWindow::removeItemRow(const QModelIndex& index)
{
    auto parentIndex = m_standardModel->parent(index);
    m_standardModel->removeRow(index.row(), parentIndex);
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
        addItemRow("111", "222", index);
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


