//
// Created by baijinde on 21-9-17.
//

#include "RoadItem.h"
#include "common.h"

RoadItem::RoadItem()
{
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setZValue(RoadItemZValue);
}

RoadItem::~RoadItem()
{}

void RoadItem::setRoad(const std::shared_ptr<t_road> road)
{
    m_ptrRoad = road;
}

std::string RoadItem::getRoadId() const
{
    return m_ptrRoad->id;
}

void RoadItem::setPolygonPoint(const QPolygonF &qpolygonPoint)
{
    m_qpolygonPoint = qpolygonPoint;
}

void RoadItem::appendLaneSectionItem(double dOffset, LaneSectionItem *pLaneSectionItem)
{
    m_mapLaneSectionItems.insert(dOffset, pLaneSectionItem);
}
