#ifndef TESTFITPARAMETERMODEL_H
#define TESTFITPARAMETERMODEL_H

#include <QtTest>
#include "JobModel.h"
#include "FitParameterAbsModel.h"
#include "FitParameterItems.h"
#include "FitSuiteItem.h"

class TestFitParameterModel : public QObject {
    Q_OBJECT

private slots:
    void test_InitialState();
    void test_addFitParameter();
    void test_addFitParameterAndLink();
};

inline void TestFitParameterModel::test_InitialState()
{
    JobModel source;
    SessionItem *fitSuiteItem = source.insertNewItem(Constants::FitSuiteType);
    SessionItem *container = source.insertNewItem(Constants::FitParameterContainerType, fitSuiteItem->index(), -1, FitSuiteItem::T_FIT_PARAMETERS);
    FitParameterAbsModel proxy(dynamic_cast<FitParameterContainerItem *>(container));

    QCOMPARE(0, proxy.rowCount(QModelIndex()));
    QCOMPARE((int)FitParameterAbsModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));
    QCOMPARE(container, proxy.itemForIndex(QModelIndex()));
}

inline void TestFitParameterModel::test_addFitParameter()
{
    JobModel source;
    SessionItem *fitSuiteItem = source.insertNewItem(Constants::FitSuiteType);
    SessionItem *container = source.insertNewItem(Constants::FitParameterContainerType, fitSuiteItem->index(), -1, FitSuiteItem::T_FIT_PARAMETERS);
    FitParameterAbsModel proxy(dynamic_cast<FitParameterContainerItem *>(container));

    // adding fit parameter
    SessionItem *fitPar0 = source.insertNewItem(Constants::FitParameterType, container->index());
    fitPar0->setDisplayName(QStringLiteral("par"));
    fitPar0->setItemValue(FitParameterItem::P_MIN, 1.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 2.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 3.0);

    QCOMPARE(1, proxy.rowCount(QModelIndex()));
    QCOMPARE((int)FitParameterAbsModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=0 (original FitParameterItem)
    QModelIndex index = proxy.index(0, 0, QModelIndex());
    QCOMPARE(index.row(), 0);
    QCOMPARE(index.column(), 0);
    QCOMPARE(proxy.rowCount(index), 0);
    QCOMPARE(proxy.columnCount(index), 5);

    QCOMPARE(fitPar0, proxy.itemForIndex(index));
    QCOMPARE(fitPar0->displayName(), proxy.data(index).toString());
    QCOMPARE(index, proxy.indexOfItem(fitPar0));

    // accessing item at col=2
    index = proxy.index(0, (int)FitParameterAbsModel::ITEM_MIN, QModelIndex());
    QCOMPARE(index.row(), 0);
    QCOMPARE(index.column(), (int)FitParameterAbsModel::ITEM_MIN);

    QCOMPARE(proxy.rowCount(index), 0);
    QCOMPARE(proxy.columnCount(index), 0);
    QCOMPARE((int)FitParameterAbsModel::ITEM_MIN, index.column());
    QCOMPARE(fitPar0->getItem(FitParameterItem::P_MIN), proxy.itemForIndex(index));
    QCOMPARE(fitPar0->getItemValue(FitParameterItem::P_MIN).toDouble(), proxy.data(index).toDouble());
    QCOMPARE(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_MIN)));

    // accessing item at col=3
    index = proxy.index(0, (int)FitParameterAbsModel::ITEM_START, QModelIndex());
    QCOMPARE(index.row(), 0);
    QCOMPARE(index.column(), (int)FitParameterAbsModel::ITEM_START);

    QCOMPARE((int)FitParameterAbsModel::ITEM_START, index.column());
    QCOMPARE(fitPar0->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    QCOMPARE(fitPar0->getItemValue(FitParameterItem::P_START_VALUE).toDouble(), proxy.data(index).toDouble());
    QCOMPARE(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_START_VALUE)));

    // accessing item at col=4
    index = proxy.index(0, (int)FitParameterAbsModel::ITEM_MAX, QModelIndex());
    QCOMPARE(index.row(), 0);
    QCOMPARE((int)FitParameterAbsModel::ITEM_MAX, index.column());
    QCOMPARE(fitPar0->getItem(FitParameterItem::P_MAX), proxy.itemForIndex(index));
    QCOMPARE(fitPar0->getItemValue(FitParameterItem::P_MAX).toDouble(), proxy.data(index).toDouble());
    QCOMPARE(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_MAX)));

    // -------------------------------
    // adding second fit parameter
    // -------------------------------
    SessionItem *fitPar1 = source.insertNewItem(Constants::FitParameterType, container->index());
    fitPar0->setDisplayName(QStringLiteral("par"));
    fitPar0->setItemValue(FitParameterItem::P_MIN, 10.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 20.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 30.0);

    QCOMPARE(2, proxy.rowCount(QModelIndex()));
    QCOMPARE((int)FitParameterAbsModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=3 for fitPar0
    index = proxy.index(0, (int)FitParameterAbsModel::ITEM_START, QModelIndex());
    QCOMPARE(0, index.row());
    QCOMPARE((int)FitParameterAbsModel::ITEM_START, index.column());
    QCOMPARE(fitPar0->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    QCOMPARE(fitPar0->getItemValue(FitParameterItem::P_START_VALUE).toDouble(), proxy.data(index).toDouble());
    QCOMPARE(index, proxy.indexOfItem(fitPar0->getItem(FitParameterItem::P_START_VALUE)));

    // accessing item at col=3 for fitPar1
    index = proxy.index(1, (int)FitParameterAbsModel::ITEM_START, QModelIndex());
    QCOMPARE(index.row(), 1);
    QCOMPARE(index.column(), (int)FitParameterAbsModel::ITEM_START);
//    QCOMPARE(index.row(), 0);
//    QCOMPARE(index.column(), 0);
    QCOMPARE(proxy.rowCount(index), 0);
    QCOMPARE(proxy.columnCount(index), 0);


    QCOMPARE((int)FitParameterAbsModel::ITEM_START, index.column());
    QCOMPARE(fitPar1->getItem(FitParameterItem::P_START_VALUE), proxy.itemForIndex(index));
    QCOMPARE(fitPar1->getItemValue(FitParameterItem::P_START_VALUE).toDouble(), proxy.data(index).toDouble());
    QCOMPARE(index, proxy.indexOfItem(fitPar1->getItem(FitParameterItem::P_START_VALUE)));


}

inline void TestFitParameterModel::test_addFitParameterAndLink()
{
    JobModel source;
    SessionItem *fitSuiteItem = source.insertNewItem(Constants::FitSuiteType);
    SessionItem *container = source.insertNewItem(Constants::FitParameterContainerType, fitSuiteItem->index(), -1, FitSuiteItem::T_FIT_PARAMETERS);
    FitParameterAbsModel proxy(dynamic_cast<FitParameterContainerItem *>(container));

    // adding fit parameter
    SessionItem *fitPar0 = source.insertNewItem(Constants::FitParameterType, container->index());
    fitPar0->setDisplayName(QStringLiteral("par"));
    fitPar0->setItemValue(FitParameterItem::P_MIN, 1.0);
    fitPar0->setItemValue(FitParameterItem::P_MAX, 2.0);
    fitPar0->setItemValue(FitParameterItem::P_START_VALUE, 3.0);

    // adding link
    SessionItem *link0 = source.insertNewItem(Constants::FitParameterLinkType, fitPar0->index());
    link0->setItemValue(FitParameterLinkItem::P_LINK, "xxx");

    QCOMPARE(1, proxy.rowCount(QModelIndex()));
    QCOMPARE((int)FitParameterAbsModel::MAX_COLUMNS, proxy.columnCount(QModelIndex()));

    // accessing item at col=0 (original FitParameterItem)
    QModelIndex index = proxy.index(0, 0, QModelIndex());
    QCOMPARE(index.row(), 0);
    QCOMPARE(index.column(), 0);
    QCOMPARE(proxy.rowCount(index), 1);
    QCOMPARE(proxy.columnCount(index), 5);
    QModelIndex linkIndex = proxy.index(0, 0, index);
    QCOMPARE(linkIndex.row(), 0);
    QCOMPARE(linkIndex.column(), 0);
    QCOMPARE(proxy.rowCount(linkIndex), 0);
    QCOMPARE(proxy.columnCount(linkIndex), 5);
    QCOMPARE(proxy.parent(linkIndex), index);
    QCOMPARE(proxy.itemForIndex(linkIndex), link0->getItem(FitParameterLinkItem::P_LINK));

    QCOMPARE(link0->getItemValue(FitParameterLinkItem::P_LINK).toString(), proxy.data(linkIndex).toString());
    qDebug() << "DDD" << linkIndex << proxy.indexOfItem(link0->getItem(FitParameterLinkItem::P_LINK));
    QCOMPARE(linkIndex, proxy.indexOfItem(link0->getItem(FitParameterLinkItem::P_LINK)));

    // adding second link
    SessionItem *link1 = source.insertNewItem(Constants::FitParameterLinkType, fitPar0->index());
    link1->setItemValue(FitParameterLinkItem::P_LINK, "yyy");


}

#endif


