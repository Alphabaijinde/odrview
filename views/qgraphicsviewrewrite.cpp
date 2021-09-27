//
// Created by baijinde on 21-9-16.
//

#include "qgraphicsviewrewrite.h"


#include <QApplication>
#include <QMouseEvent>
#include <QScrollBar>

#ifndef SCALE_MIN
#define SCALE_MIN (12) //测试发现的倍率
#endif

#ifndef SCALE_MUL
#define SCALE_MUL (1.1) //扩大倍数
#endif

const double dMaxScale = 63;
const double dMinScale = 0.05;


QGraphicsViewRewrite::QGraphicsViewRewrite(QWidget *parent):QGraphicsView(parent)
{
    m_bActive = false;
    setMouseTracking(true);

    // 设置已鼠标为中心进行缩放
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void QGraphicsViewRewrite::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pointf = mapToScene(event->pos()); //QGraphicsView的坐标转场景坐标
    emit mouseMovePoint(pointf); //释放信号
    QGraphicsView::mouseMoveEvent(event);

    static QPoint PrePoint(0, 0);
    if(event->buttons() & Qt::MidButton)
    {
        emit sigChangeCursor(QCursor(Qt::PointingHandCursor));
        QPoint offset = event->pos() - PrePoint;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - offset.rx());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - offset.ry());
    }

    PrePoint = event->pos();
}

void QGraphicsViewRewrite::mousePressEvent(QMouseEvent *event)
{
    //鼠标左右键同时按下,不做任何操作
    if(event->buttons() == (Qt::LeftButton | Qt::RightButton))
    {
        return;
    }

    if(event->button()==Qt::LeftButton)
    {
        QPointF pointf = mapToScene(event->pos()); //QGraphicsView坐标转为QGraphicsScene坐标
        emit mouseClicked(pointf);//释放信号
    }

    if(!m_bActive)
    {
        QGraphicsView::mousePressEvent(event);
    }
    else
    {
        m_bActive = false;
    }
}

void QGraphicsViewRewrite::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPointF pointf = mapToScene(event->pos()); //QGraphicsView的坐标转场景坐标
        emit mouseReleasePoint(pointf);//释放信号
    }
    else if(event->button() == Qt::RightButton)
    {
        QPointF pointf = mapToScene(event->pos()); //QGraphicsView的坐标转场景坐标
        emit mouseRightReleasePoint(pointf);//释放信号
    }
    else if(event->button() == Qt::MidButton)
    {
        emit sigChangeCursor(Qt::ArrowCursor);
    }

    if(!m_bActive)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    else
    {
        m_bActive = false;
    }
}

void QGraphicsViewRewrite::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        QPoint point=event->pos(); //QGraphicsView的坐标
        emit mouseDoubleClick(point);//释放信号
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void QGraphicsViewRewrite::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}

void QGraphicsViewRewrite::wheelEvent(QWheelEvent *event)
{
//    if(event->delta() > 0)
//    {
//        // 向上滚动，放大;
//        this->scale(SCALE_MUL, SCALE_MUL);
//    }
//    else
//    {
//        // 向下滚动，缩小;
//        if(transform().m11() >= __MAPFILESIZE->getMapScale() / SCALE_MIN)
//        {
//            this->scale(1 / SCALE_MUL, 1 / SCALE_MUL);
//        }
//    }

    if(Qt::ControlModifier == QApplication::keyboardModifiers())
    {
        if(event->delta() > 0)      // 向上滚动，场景上移
        {
            verticalScrollBar()->setValue(verticalScrollBar()->value() - 20);
        }
        else                        // 向下滚动，场景下移
        {
            verticalScrollBar()->setValue(verticalScrollBar()->value() + 20);
        }
    }
    else
    {
        if(event->delta() > 0)      // 向上滚动，放大
        {
            if(dMaxScale < this->transform().m11())
            {
                return;
            }

            this->scale(SCALE_MUL, SCALE_MUL);
        }
        else                        // 向下滚动，缩小
        {
            if(dMinScale > this->transform().m11())
            {
                return;
            }

            this->scale(1 / SCALE_MUL, 1 / SCALE_MUL);
        }
    }
    //QGraphicsView::wheelEvent(event);
}

void QGraphicsViewRewrite::setActive(bool bActive)
{
    m_bActive = bActive;
}