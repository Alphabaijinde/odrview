//
// Created by baijinde on 21-9-17.
//

#include "RoadMapItem.h"
#include "common.h"

RoadMapItem::RoadMapItem()
{
    setZValue(RoadMapItemZValue);
}

RoadMapItem::~RoadMapItem()
{}

void RoadMapItem::onMap(const QPointF &pointf, const QVariant &laneInfo)
{
    emit sigSendMapInfo(pointf, laneInfo);
}

void RoadMapItem::appendRoadItem(RoadItem *pRoadItem)
{
    m_mapRoadIDAndRoadItem.insert(pRoadItem->getRoadId(), pRoadItem);
}
