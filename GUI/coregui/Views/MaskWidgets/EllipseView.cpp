#include "EllipseView.h"
#include "EllipseItem.h"
#include "ParameterizedItem.h"
#include <cmath>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QDebug>

static const qreal widthAndHeight = 10;
static const qreal OffsetPosition = 5;

EllipseView::EllipseView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIgnoresTransformations, false);
}

void EllipseView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    // paint rectangle
    painter->setRenderHints(QPainter::Antialiasing);
    this->prepareGeometryChange();
    if (m_item->getRegisteredProperty(EllipseItem::P_COLOR).toBool() == 0) {
        QBrush transRed(QColor(0xFF, 0, 0, 0x80));
        painter->setBrush(transRed);
        painter->drawEllipse(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());
    } else {
        QBrush transBlue(QColor(0, 0, 0xFF, 0x80));
        painter->setBrush(transBlue);
        painter->drawEllipse(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal(),
                             m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal());
    }

    // paint corner rectangles only if this item is selected
    if (this->isSelected()) {

        painter->setBrush(Qt::green);
        painter->drawRect(getTopLeftCorner());
        painter->drawRect(getBottomLeftCorner());
        painter->drawRect(getTopRightCorner());
        painter->drawRect(getBottomRightCorner());
    }
}

QRectF EllipseView::boundingRect() const
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - 5,
                  m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() + 10,
                  m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() + 10);
}

void EllipseView::checkResizeRules(QGraphicsSceneMouseEvent *event)
{
    if (m_corner == TOPLEFT) {
        if (m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() +
                m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);
        }
    } else if (m_corner == TOPRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                   + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal()
                   <= event->pos().y()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMLEFT) {
        if (m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() <= event->pos().x()) {
            m_corner = BOTTOMRIGHT;
            setCursor(Qt::SizeFDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()) {
            m_corner = TOPLEFT;
            setCursor(Qt::SizeFDiagCursor);
        }
    } else if (m_corner == BOTTOMRIGHT) {
        if (event->pos().x() <= m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()) {
            m_corner = BOTTOMLEFT;
            setCursor(Qt::SizeBDiagCursor);

        } else if (event->pos().y() <= m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()) {
            m_corner = TOPRIGHT;
            setCursor(Qt::SizeBDiagCursor);
        }
    }
}

void EllipseView::calculateResize(QGraphicsSceneMouseEvent *event)
{
    checkResizeRules(event);
    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).
                                      toReal() - event->pos().x());

        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).
                                      toReal() - event->pos().y());

        m_item->setRegisteredProperty(EllipseItem::P_POSX, event->pos().x());
        m_item->setRegisteredProperty(EllipseItem::P_POSY, event->pos().y());

    }
    else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal()
                                      - event->pos().x());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_POSX, event->pos().x());

    }
    else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT,
                                      m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                                      + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT)
                                      .toReal() - std::abs(event->pos().y()));
        m_item->setRegisteredProperty(EllipseItem::P_POSY, event->pos().y());
    }
    else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_WIDTH, event->pos().x()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal());
        m_item->setRegisteredProperty(EllipseItem::P_HEIGHT, event->pos().y()
                                      - m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());
    }
}

qreal EllipseView::getRotationAngle(QGraphicsSceneMouseEvent *event)
{
    QPointF middlePoint
        = mapToScene(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                     + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2,
                     m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                     + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() / 2);
    qreal lengthOfHypotenuse
        = sqrt(pow(m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2, 2)
               + pow(m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() / 2, 2));
    qreal offsetAngle = acos((m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() / 2)
                             / lengthOfHypotenuse) * 180 / M_PI;
    qreal radians = atan((event->scenePos().y() - middlePoint.y())
                         / (event->scenePos().x() - middlePoint.x()));

    if (m_corner == TOPLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;

    } else if (m_corner == TOPRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMLEFT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI + offsetAngle - 180);
        return  radians * 180 / M_PI + offsetAngle - 180;

    } else if (m_corner == BOTTOMRIGHT) {
        m_item->setRegisteredProperty(EllipseItem::P_ANGLE, radians * 180 / M_PI - offsetAngle);
        return radians * 180 / M_PI - offsetAngle;
    }
    return 0.0;
}

void EllipseView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setFlag(QGraphicsItem::ItemIsMovable, false);

    if (event->button() == Qt::LeftButton) {
        setSelectedCorner(event);

        if (m_corner == NONE) {
            if ((m_mode == RESIZE)) {
                m_mode = ROTATION;
            } else if ((m_mode == ROTATION)) {
                m_mode = RESIZE;
            }
            this->setFlag(QGraphicsItem::ItemIsMovable, true);
            QGraphicsItem::mousePressEvent(event);
        }
    }
}

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // check which mode is active and process with the active mode
    if (m_mode == RESIZE && m_corner != NONE) {
        calculateResize(event);
    } else if (m_corner != NONE && m_mode == ROTATION) {
        QTransform transform;
        transform.translate(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                            + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5,
                            m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                            + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5);
        transform.rotate(getRotationAngle(event));
        transform.translate(-(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                              + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5),
                            -(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                              + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5));
        setTransform(transform);
//         process as usual
    } else {
        this->setFlag(QGraphicsItem::ItemIsMovable, true);
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void EllipseView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // set all modes off, change cursor and process as usual
    //    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    //    m_mode = SELECTION;
    m_corner = NONE;
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

void EllipseView::setInclude()
{
    m_item->setRegisteredProperty(EllipseItem::P_COLOR, 0);
}

void EllipseView::setExclude()
{
    m_item->setRegisteredProperty(EllipseItem::P_COLOR, 1);
}

QRectF EllipseView::getTopLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getTopRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getBottomLeftCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

QRectF EllipseView::getBottomRightCorner()
{
    return QRectF(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() - OffsetPosition,
                  m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                  + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() - OffsetPosition,
                  widthAndHeight, widthAndHeight);
}

void EllipseView::setParameterizedItem(ParameterizedItem *item)
{
    m_item = item;
    setX(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal());
    setY(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal());
    setRotation(m_item->getRegisteredProperty(EllipseItem::P_ANGLE).toReal());
    connect(m_item, SIGNAL(propertyChanged(const QString &)), this,
            SLOT(onPropertyChange(const QString &)));
    initializeArrow();
}

void EllipseView::onChangedX()
{
//    m_block_update = true;
//    qDebug() << "onXValueChanged(double xValue)-> x value changed" << x();
//    m_item->setRegisteredProperty(EllipseItem::P_POSX, x());
//    m_block_update = false;
}

void EllipseView::onChangedY()
{
//    m_block_update = true;
//    qDebug() << "onYValueChanged(double yValue)-> y value changed" << y();
//    m_item->setRegisteredProperty(EllipseItem::P_POSY, y());
//    m_block_update = false;
}

void EllipseView::onPropertyChange(const QString &propertyName)
{
    if(propertyName == EllipseItem::P_ANGLE) {
    QTransform transform;
    transform.translate(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                        + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5,
                        m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                        + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5);
    transform.rotate(m_item->getRegisteredProperty(EllipseItem::P_ANGLE).toReal());
    transform.translate(-(m_item->getRegisteredProperty(EllipseItem::P_POSX).toReal()
                          + m_item->getRegisteredProperty(EllipseItem::P_WIDTH).toReal() * 0.5),
                        -(m_item->getRegisteredProperty(EllipseItem::P_POSY).toReal()
                          + m_item->getRegisteredProperty(EllipseItem::P_HEIGHT).toReal() * 0.5));
    setTransform(transform);
    }

}

ParameterizedItem *EllipseView::getParameterizedItem()
{
    return m_item;
}

void EllipseView::setSelectedCorner(QGraphicsSceneMouseEvent *event)
{
    if (getTopLeftCorner().contains(event->pos())) {
        qDebug() << "TOPLEFT";
        m_corner = TOPLEFT;
        setCursor(Qt::SizeFDiagCursor);
    } else if (getTopRightCorner().contains(event->pos())) {
        qDebug() << "TOPRIGHT";
        m_corner = TOPRIGHT;
        setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomLeftCorner().contains(event->pos())) {
        qDebug() << "BOTTOMLEFT";
        m_corner = BOTTOMLEFT;
        setCursor(Qt::SizeBDiagCursor);
    } else if (getBottomRightCorner().contains(event->pos())) {
        qDebug() << "BOTTOMRIGHT";
        m_corner = BOTTOMRIGHT;
        setCursor(Qt::SizeFDiagCursor);
    } else {
        m_corner = NONE;
    }

    if (m_mode == ROTATION) {
        setCursor(Qt::ClosedHandCursor);
    }
}

void EllipseView::updateRotationArrows()
{
//    childItems()[1]->setX(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal());
//    childItems()[2]->setY(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());
//    childItems()[3]->setPos(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
//                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());
//    if(m_mode == RESIZE) {
//        for(int i = 0; i < childItems().length(); ++i) {
//            childItems()[i]->setVisible(false);
//        }
//    }
//    else if(m_mode == ROTATION) {
//        for(int i = 0; i < childItems().length(); ++i) {
//            childItems()[i]->setVisible(true);
//        }
//    }
}

void EllipseView::initializeArrow()
{
//    RotationArrow *topLeftArrow = new RotationArrow(this);
//    RotationArrow *topRightArrow = new RotationArrow(this);
//    RotationArrow *bottomLeftArrow = new RotationArrow(this);
//    RotationArrow *bottomRightArrow = new RotationArrow(this);

//    topRightArrow->setRotation(90);
//    topRightArrow->setX(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal());
//    bottomLeftArrow->setRotation(270);
//    bottomLeftArrow->setY(m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());
//    bottomRightArrow->setRotation(180);
//    bottomLeftArrow->setPos(m_item->getRegisteredProperty(RectangleItem::P_WIDTH).toReal(),
//                            m_item->getRegisteredProperty(RectangleItem::P_HEIGHT).toReal());

//    topRightArrow->setVisible(false);
//    topLeftArrow->setVisible(false);
//    bottomLeftArrow->setVisible(false);
//    bottomRightArrow->setVisible(false);
}
