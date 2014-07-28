#ifndef SAMPLETUNINGDELEGATE_H
#define SAMPLETUNINGDELEGATE_H

#include <QItemDelegate>
#include "ItemLink.h"

class QDoubleSpinBox;
class QHBoxLayout;

class SampleTuningDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    SampleTuningDelegate(int valueColumn, QObject *parent = 0);

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & /* index */) const
    {
        return QSize(option.rect.width(),25);
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;


private slots:
    void sliderValueChanged(int position);
    void editorValueChanged(double value);

private:
    int m_valueColumn;
    mutable QSlider *m_slider;
    mutable QDoubleSpinBox *m_valueBox;
    mutable QWidget *m_contentWidget;
    mutable QHBoxLayout * m_contentLayout;
    double m_multiplyFactor;
    mutable ItemLink m_current_link;
};

#endif //SAMPLETUNINGDELEGATE_H
