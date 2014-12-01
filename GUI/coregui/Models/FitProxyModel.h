#ifndef FITPROXYMODEL_H
#define FITPROXYMODEL_H


#include <QAbstractItemModel>

class FitModel;
class ParameterizedItem;

class BA_CORE_API_ FitProxyModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FitProxyModel(QObject *parent = 0);
    ~FitProxyModel(){}

    // overriden methods
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parentIndex) const;
    int columnCount(const QModelIndex &parentIndex) const;
    QModelIndex index(int row, int column, const QModelIndex &parentIndex) const;
    QModelIndex parent(const QModelIndex &child) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    //end if overriden methods

    void setFitModel(FitModel *fitModel);
    FitModel *getFitModel()
        { return m_fitModel; }

    ParameterizedItem *itemForIndex(const QModelIndex &index) const;


private:
    FitModel *m_fitModel;

};




#endif