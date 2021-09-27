//
// Created by baijinde on 21-9-17.
//

#ifndef ODRVIEWER_ROADITEM_H
#define ODRVIEWER_ROADITEM_H


#include <QGraphicsItemGroup>
#include <QMap>
#include "xodr.h"
#include "LaneSectionItem.h"


class RoadItem : public QObject, public QGraphicsItemGroup {

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit RoadItem();
    virtual ~RoadItem();

    void setRoad(const std::shared_ptr<t_road> road);
    std::string getRoadId() const;
    void setPolygonPoint(const QPolygonF &qpolygonPoint);
    void appendLaneSectionItem(double dOffset, LaneSectionItem *pLaneSectionItem);

private:
    std::shared_ptr<t_road> m_ptrRoad;
    QPolygonF m_qpolygonPoint;

    // 管理道路的车道段图元
    QMap<double, LaneSectionItem *> m_mapLaneSectionItems;
};


#endif //ODRVIEWER_ROADITEM_H
