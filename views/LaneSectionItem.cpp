//
// Created by baijinde on 21-9-17.
//

#include "LaneSectionItem.h"

#include <stdlib.h>
#include <assert.h>
#include <float.h>

#include <QPen>
#include <QPainter>

#include "common.h"
#include "../model/MapInfo.h"

LaneSectionItem::LaneSectionItem(std::string strRoadId)
{
    setZValue(LaneSectionItemZValue);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemStacksBehindParent);

    m_strRoadId = strRoadId;
}

LaneSectionItem::~LaneSectionItem()
{}

void LaneSectionItem::setLaneSection(const std::shared_ptr<t_road_lanes_laneSection> &laneSection, int index)
{
    m_ptrLaneSection = laneSection;
    m_index = index;
}

void LaneSectionItem::setPolygonPoint(const QPolygonF &qpolygonPoint)
{
    m_qLaneSectionPolygonPoint = qpolygonPoint;
}

void LaneSectionItem::appendLaneLine(std::string strLaneID, const Painting laneLine)
{
    m_qmapLaneLine.insertMulti(strLaneID, laneLine);
}

void LaneSectionItem::appendFilling(std::string strRoadID, const Painting filling)
{
//    m_qmapFilling.insertMulti(strRoadID, filling);
//    auto iter = m_qmapLanetypeFilling.find(filling.qstrColor.toStdString());
//    if(iter != m_qmapLanetypeFilling.end())
//    {
//        iter.value().append(filling);
//    }
//    else
//    {
//        m_qmapLanetypeFilling[filling.qstrColor.toStdString()] += filling;
//    }

    // none border shoulder stop restricted parking sidewalk biking entry exit driving
    if(filling.qstrColor == "none")
    {
        m_qvecNoneTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "median")
    {
        m_qvecMedianTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "bidirectional")
    {
        m_qvecBidirectionalTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "border")
    {
        m_qvecBorderTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "shoulder")
    {
        m_qvecShoulderTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "stop")
    {
        m_qvecStopTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "restricted")
    {
        m_qvecRestrictedTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "parking")
    {
        m_qvecParkingTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "sidewalk")
    {
        m_qvecSidewalkTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "biking")
    {
        m_qvecBikingTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "entry" || filling.qstrColor == "onRamp")
    {
        m_qvecEntryTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "exit" || filling.qstrColor == "offRamp")
    {
        m_qvecExitTypeFilling.append(filling);
    }
    else if(filling.qstrColor == "driving")
    {
        m_qvecDrivingTypeFilling.append(filling);
    }
    else
    {
        assert("lane type is new");
    }
}

void LaneSectionItem::setLanePolygonPoint(std::string strLaneId, const QPolygonF &qpolygonPoint)
{
    m_qmapLanePolygonPoint.insert(strLaneId, qpolygonPoint);
}

void LaneSectionItem::appendLanePolygon(const QPolygonF &lanePolygon, std::string roadId, const std::shared_ptr<t_road_lanes_laneSection> &laneSection, const std::shared_ptr<t_road_planView_geometry> &geometry, std::string laneId)
{
    m_qmapAllLanePolygon.insert(m_qmapAllLanePolygon.size(), lanePolygon);

    RoadPos roadPos = {roadId, laneSection, geometry, laneId};

    m_qmapLaneInfo.insert(m_qmapAllLanePolygon.size()-1, roadPos);
}

void LaneSectionItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    auto iter = m_qmapAllLanePolygon.begin();
    for(; iter != m_qmapAllLanePolygon.end(); ++iter)
    {
        if(iter.value().containsPoint(event->pos(), Qt::WindingFill))
        {
            if(m_qmapLaneInfo.find(iter.key()) != m_qmapLaneInfo.end())
            {
                QVariant info;
                info.setValue(m_qmapLaneInfo[iter.key()]);
                emit sigCurPosInfo(event->pos(), info);
            }
        }
    }
}

QColor LaneSectionItem::getColor(std::string qstrType)
{
    if(m_qmapColor.isEmpty())
    {
        m_qmapColor[STR_RAIL] = QColor(190, 147, 120);
        m_qmapColor[STR_RESTRICTED] = QColor(133, 152, 103);
        m_qmapColor[STR_MEDIAN] = QColor(133, 152, 103);
        m_qmapColor[STR_STOP] = QColor(106, 90, 90);
        m_qmapColor[STR_NONE] = QColor(190, 147, 120, 128);
        m_qmapColor[STR_BORDER] = QColor(70, 82, 122);
        m_qmapColor[STR_BIKING] = QColor(104, 200, 172);
        m_qmapColor[STR_PARKING] = QColor(96, 145, 212);
        m_qmapColor[STR_SIDEWALK] = QColor(188, 193, 203);
        m_qmapColor[STR_DRIVING] = QColor(160, 160, 160);
        m_qmapColor[STR_BIDIRECTIONAL] = QColor(160, 160, 160);
        m_qmapColor[STR_EXIT] = QColor(165, 175, 194);
        m_qmapColor[STR_OFFRAMP] = QColor(165, 175, 194);
        m_qmapColor[STR_ENTRY] = QColor(224, 192, 195);
        m_qmapColor[STR_ONRAMP] = QColor(224, 192, 195);
        m_qmapColor[STR_SHOULDER] = QColor(154, 199, 163);
        m_qmapColor[STR_STANDARD] = Qt::white;
        m_qmapColor[STR_BLUE] = Qt::blue;
        m_qmapColor[STR_GREEN] = Qt::green;
        m_qmapColor[STR_RED] = Qt::red;
        m_qmapColor[STR_WHITE] = Qt::white;
        m_qmapColor[STR_YELLOW] = Qt::yellow;
        m_qmapColor[STR_ORANGE] = QColor(255,165,0);
    }

    return m_qmapColor.find(qstrType) == m_qmapColor.end() ? Qt::color0 : m_qmapColor.value(qstrType);
}

void LaneSectionItem::drawPathAndColor(QPainter *&painter, const Painting &filling)
{
    QPen pen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(getColor(filling.qstrColor));

    QPainterPath path;
    path.addPolygon(filling.polygonF);
    path.setFillRule(Qt::WindingFill);

    painter->drawPath(path);
}

void LaneSectionItem::drawRoadMark(QPainter *&painter)
{
    QPen pen(Qt::NoPen);
    painter->setPen(pen);

    QMap<std::string, Painting>::iterator laneLine = m_qmapLaneLine.begin();
    for(; laneLine != m_qmapLaneLine.end(); ++laneLine)
    {
        pen.setColor(getColor(laneLine.value().qstrColor));
        pen.setStyle(Qt::SolidLine);

        if(fabs(laneLine.value().width-0.0) < DBL_EPSILON)
        {
            pen.setWidthF(LANE_LINE_WIDTHF);
        }
        else
        {
            pen.setWidthF(laneLine.value().width);
        }

        pen.setCapStyle(Qt::FlatCap);
        painter->setPen(pen);

        painter->drawPolyline(laneLine.value().polygonF);
    }
}

QRectF LaneSectionItem::boundingRect() const
{
    return QRectF(m_qLaneSectionPolygonPoint.boundingRect().topLeft().rx()-5, m_qLaneSectionPolygonPoint.boundingRect().topLeft().ry()-5,
            m_qLaneSectionPolygonPoint.boundingRect().width()+10, m_qLaneSectionPolygonPoint.boundingRect().height()+10);
}

void LaneSectionItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setRenderHint(QPainter::Antialiasing);

    //填充
    for(auto filling : m_qvecNoneTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecMedianTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecBidirectionalTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecBorderTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecShoulderTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecStopTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecRestrictedTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecParkingTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecSidewalkTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecBikingTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecEntryTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecExitTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    for(auto filling : m_qvecDrivingTypeFilling)
    {
        drawPathAndColor(painter, filling);
    }

    //车道线
    drawRoadMark(painter);
}
