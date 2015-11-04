#include "ObsoletePolygonView.h"
#include "ParameterizedItem.h"
#include "ObsoletePolygonItem.h"
#include "ObsoletePointItem.h"
#include <cmath>
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>

ObsoletePolygonView::ObsoletePolygonView()
    : m_changeCornerMode(false), m_indexOfCurrentSelectedPoint(0), m_mouseIsOverFirstPoint(false)

{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->cursor().setShape(Qt::ClosedHandCursor);
    this->setAcceptHoverEvents(true);
}

void ObsoletePolygonView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen pen;
    prepareGeometryChange();
    painter->setRenderHints(QPainter::Antialiasing);
    QList<ParameterizedItem *> points = m_item->childItems();
    QPolygon polygon;

    // draws polygon
    for (int i = 0; i < points.length(); ++i) {
        polygon << QPoint(points[i]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal(),
                          points[i]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal());
    }
    painter->drawPolyline(polygon);

    // fills polygon with a color
    if (getFirstPoint().center().x() == polygon[polygon.length() - 1].x()
        && getFirstPoint().center().y() == polygon[polygon.length() - 1].y()
        && points.length() >= 2) {

        QPainterPath path;
        QBrush transRed(DesignerHelper::getDefaultColor("Transparant red"));
        QBrush transBlue(DesignerHelper::getDefaultColor("Transparant blue"));
        path.moveTo(polygon[0].x(),polygon[0].y());
        for (int i = 1; i < polygon.length(); ++i) {
            path.lineTo(polygon[i].x(), polygon[i].y());
        }
        painter->setPen(Qt::NoPen);
        if (m_item->getRegisteredProperty(ObsoletePolygonItem::P_COLOR).toInt() == 0) {
            painter->fillPath(path, transRed);
        } else {
            painter->fillPath(path, transBlue);
        }
    }

    if (points.length() >= 1
        && m_item->getRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE).toBool()) {
        pen.setWidth(1);
        if (m_mouseIsOverFirstPoint) {
            painter->fillRect(getFirstPoint(), Qt::red);
        } else {
            painter->drawRect(getFirstPoint());
        }
    }
    // draw all points if item is finised with drawing and is selected
    if (!m_item->getRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE).toBool() && isSelected()) {
        pen.setWidth(5);
        painter->setPen(pen);
        for (int i = 0; i < points.length() - 1; ++i) {
            painter->drawPoint(
                QPointF(polygon[i].x(), polygon[i].y()));
        }
        painter->setPen(QPen());
    }
}

QRectF ObsoletePolygonView::boundingRect() const
{
    if (m_item->childItems().length() >= 1) {
        return calculateBoundingRectangle();
    } else {
        return QRectF(0, 0, 20, 20);
    }
}

bool ObsoletePolygonView::isCornerClicked(QGraphicsSceneMouseEvent *event)
{
    QList<ParameterizedItem *> points = m_item->childItems();
    for (int i = 0; i < points.length() - 1; ++i) {
        QRectF rectangle(
            points[i]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal() - 2.5,
            points[i]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal() - 2.5, 5, 5);
        if (rectangle.contains(event->pos())) {
            if (i != points.length() - 1 && i != 0) {
                m_indexOfCurrentSelectedPoint = i;
            } else {
                m_indexOfCurrentSelectedPoint = 0;
            }
            m_changeCornerMode = true;
            this->setFlag(QGraphicsItem::ItemIsMovable, false);
            return true;
        }
    }
    return false;
}

QRectF ObsoletePolygonView::calculateBoundingRectangle() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    qreal smallestXValue = points[0]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal();
    qreal biggestXValue = points[0]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal();
    qreal smallestYValue = points[0]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal();
    qreal biggestYValue = points[0]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal();


    for (int i = 1; i < points.length(); ++i) {
        smallestXValue = std::min(smallestXValue, points[i]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal());
        biggestXValue = std::max(biggestXValue, points[i]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal());
        smallestYValue = std::min(smallestYValue, points[i]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal());
        biggestYValue = std::max(biggestYValue, points[i]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal());
    }
    return QRectF(QPointF(smallestXValue - 20, smallestYValue - 20),
                  QPointF(biggestXValue + 20, biggestYValue + 20));
}

void ObsoletePolygonView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isCornerClicked(event)) {
        m_changeCornerMode = true;
    } else if (event->button() == Qt::RightButton) {
        m_item->setRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE, false);
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mousePressEvent(event);
    }
}

void ObsoletePolygonView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_changeCornerMode) {
        QList<ParameterizedItem *> points = m_item->childItems();
        setCursor(Qt::CrossCursor);
        if (m_indexOfCurrentSelectedPoint == 0) {
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(ObsoletePointItem::P_POSX, event->pos().x());
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(ObsoletePointItem::P_POSY, event->pos().y());
            points[points.length() - 1]->setRegisteredProperty(ObsoletePointItem::P_POSX, event->pos().x());
            points[points.length() - 1]->setRegisteredProperty(ObsoletePointItem::P_POSY, event->pos().y());
        } else {
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(ObsoletePointItem::P_POSX, event->pos().x());
            points[m_indexOfCurrentSelectedPoint]->setRegisteredProperty(ObsoletePointItem::P_POSY, event->pos().y());
        }
    } else if (!m_item->getRegisteredProperty(ObsoletePolygonItem::P_DRAWINGMODE).toBool()) {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void ObsoletePolygonView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_changeCornerMode = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void ObsoletePolygonView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(getFirstPoint().contains(event->pos())) {
        m_mouseIsOverFirstPoint =  true;
    }
    else {
         m_mouseIsOverFirstPoint =  false;
    }
    QGraphicsItem::hoverMoveEvent(event);
}

void ObsoletePolygonView::setInclude()
{
    m_item->setRegisteredProperty(ObsoletePolygonItem::P_COLOR, 0);
}

QRectF ObsoletePolygonView::getFirstPoint() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    return QRectF(points[0]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal() - 2.5,
                  points[0]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal() - 2.5, 5, 5);
}

QPointF ObsoletePolygonView::getLastPoint() const
{
    QList<ParameterizedItem *> points = m_item->childItems();
    int indexOfLastPoint = points.length() - 1;
    return QPointF(points[indexOfLastPoint]->getRegisteredProperty(ObsoletePointItem::P_POSX).toReal(),
                   points[indexOfLastPoint]->getRegisteredProperty(ObsoletePointItem::P_POSY).toReal());
}

ParameterizedItem *ObsoletePolygonView::getParameterizedItem()
{
    return m_item;
}

void ObsoletePolygonView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    disconnect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    disconnect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));
    connect(m_item, SIGNAL(propertyChanged(QString)), this, SLOT(onPropertyChange(QString)));
}

void ObsoletePolygonView::setExclude()
{
    m_item->setRegisteredProperty(ObsoletePolygonItem::P_COLOR, 1);
}
