//
// Created by baijinde on 21-9-17.
//

#ifndef ODRVIEWER_ROADMAPITEM_H
#define ODRVIEWER_ROADMAPITEM_H

#include <QObject>
#include <QGraphicsItemGroup>

#include "RoadItem.h"

class RoadMapItem : public QObject, public QGraphicsItemGroup {

    Q_OBJECT

public:
    explicit RoadMapItem();
    virtual ~RoadMapItem();

    void appendRoadItem(RoadItem *pRoadItem);

signals:
    void sigSendMapInfo(const QPointF &pointf, const QVariant &laneInfo);

public slots:
    void onMap(const QPointF &pointf, const QVariant &laneInfo);

private:
    QMap<std::string, RoadItem*> m_mapRoadIDAndRoadItem;
};


#endif //ODRVIEWER_ROADMAPITEM_H
