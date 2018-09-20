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


// TODO - add dat memeber to define if groups are colapsed or expanded
class ModelData {
public:
    
    ModelData(int type, const QString& label1, const QString& label2);
    QString type() const { return m_type; }
    QString label1() const { return m_label1; }
    QString label2() const { return m_label2; }
private:
    const int m_type;
    const QString m_label1;
    const QString m_label2;
};

// TODO replace MainWindow by the qwidget of yout choice
// TODO persist data at exit
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    MyTreeview *m_treeView;
    QStandardItemModel *m_standardModel;
    QModelIndex m_rootIndex;
    QStandardItem *m_rootItem;

public:
    void initializeModel(const QList<ModelData> &data);
    bool fetchModel(const QString& group, QList<ModelData> &data);
private:

    void addItemRow(
        const QString &first,
        const QString &second,
        const QModelIndex &parent);
    void removeItemRow(const QModelIndex& index);

public slots:
    void rowClicked(const QModelIndex &index);

public:

    MainWindow(QWidget *parent = 0);
};

