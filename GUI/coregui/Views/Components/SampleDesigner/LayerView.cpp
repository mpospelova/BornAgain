#include "LayerView.h"
#include "Units.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QCursor>
#include <QApplication>
#include <QMimeData>
#include <QBitmap>
#include <QWidget>
#include <QGradient>
#include <QStyleOptionGraphicsItem>

#include "DesignerHelper.h"
#include <iostream>


LayerView::LayerView(QGraphicsItem *parent)
    : ISampleRectView(parent)
    , m_fixed_xpos(0)
    , m_fixed(false)
    , m_thickness(10*Units::nanometer)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256) );
    setRectangle(QRect(0, 0, DesignerHelper::getDefaultLayerWidth(), DesignerHelper::getDefaultLayerHeight()));
    setName(QString("Layer"));
    setToolTip(QString("%1\n%2").arg("LayerView").arg("Homogeneous layer"));
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptDrops(false);

    m_materialProperty.setName("XXXXX");

    addPort(" ", NodeEditorPort::Input, NodeEditorPort::ParticleFactory);

}


void LayerView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }

    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle() ) );
    painter->drawRect(getRectangle());
}


void LayerView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mouseMoveEvent -> " << x() << " " << y() << std::endl;
    QGraphicsObject::mouseMoveEvent(event);
}

void LayerView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mousePressEvent -> " << x() << " " << y() << std::endl;
    // remove selection from child items
    QList<QGraphicsItem *> list = childItems();
    foreach(QGraphicsItem *item, list) {
        item->setSelected(false);
    }

    QGraphicsObject::mousePressEvent(event);
}

void LayerView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    std::cout << "LayerView::mouseReleaseEvent -> " << x() << " " << y() << std::endl;
    emit LayerMoved();
    QGraphicsObject::mouseReleaseEvent(event);
//    setCursor(Qt::ArrowCursor);
}


void LayerView::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragEnterEvent() ->" << std::endl;
}

void LayerView::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragLeaveEvent() ->" << std::endl;
}

void LayerView::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dropEvent() ->" << std::endl;

}

void LayerView::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    std::cout << "LayerView::dragMoveEvent() ->" << std::endl;
}

// layers are not allowed to move horizontally
QVariant LayerView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    std::cout << "YYY itemChange " << x() << " " << y() <<  std::endl;
     if (change == ItemPositionChange && scene() && m_fixed) {
         // value is the new position.
         QPointF newPos = value.toPointF();
//         QRectF rect = parentItem()->boundingRect();
//         //std::cout << "rect " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << std::endl;
//         rect.setY(rect.y() - boundingRect().height()/2.);
//         rect.setHeight(rect.height() - boundingRect().height()/2.);
//         //std::cout << "rect " << rect.x() << " " << rect.y() << " " << rect.width() << " " << rect.height() << std::endl;
//         if (!rect.contains(newPos)) {
//             // Keep the item inside the scene rect.
//             newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
//         }
         newPos.setX(m_fixed_xpos);
         return newPos;
     }
     return QGraphicsItem::itemChange(change, value);
 }


