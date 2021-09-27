//
// Created by baijinde on 21-9-16.
//

#ifndef ODRVIEWER_QGRAPHICSVIEWREWRITE_H
#define ODRVIEWER_QGRAPHICSVIEWREWRITE_H

#include <QObject>
#include <QGraphicsView>


class QGraphicsViewRewrite : public QGraphicsView
{
    Q_OBJECT

public:
    QGraphicsViewRewrite(QWidget *parent=0);
    virtual ~QGraphicsViewRewrite() {}

    void setActive(bool bActive);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent  *event);

    signals:

    void mouseMovePoint(QPointF point); //鼠标移动
    void mouseClicked(QPointF point); //鼠标单击
    void mouseReleasePoint(QPointF point); //鼠标单击
    void mouseRightReleasePoint(QPointF point); //鼠标右键释放
    void mouseDoubleClick(QPointF point); //双击事件
    void keyPress(QKeyEvent *event); //按键事件

    void sigChangeCursor(QCursor cursor); //改变鼠标形状

private:
    bool m_bActive;
};


#endif //ODRVIEWER_QGRAPHICSVIEWREWRITE_H
