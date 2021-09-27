//
// Created by baijinde on 21-9-17.
//

#ifndef ODRVIEWER_LANESECTIONITEM_H
#define ODRVIEWER_LANESECTIONITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsSceneMouseEvent>

#include "xodr.h"
#include "../util/ComputeParameter.h"

class LaneSectionItem : public QObject, public QGraphicsItemGroup {

    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    explicit LaneSectionItem(std::string strRoadId);
    virtual ~LaneSectionItem();

    void setLaneSection(const std::shared_ptr<t_road_lanes_laneSection> &laneSection, int index);
    void setPolygonPoint(const QPolygonF &qpolygonPoint);
    void appendLaneLine(std::string strLaneID, const Painting laneLine);
    void appendFilling(std::string strRoadID, const Painting filling);
    void setLanePolygonPoint(std::string strLaneId, const QPolygonF &qpolygonPoint);
    void appendLanePolygon(const QPolygonF &lanePolygon, std::string roadId, const std::shared_ptr<t_road_lanes_laneSection> &laneSection, const std::shared_ptr<t_road_planView_geometry> &geometry, std::string laneId);

signals:
    void sigCurPosInfo(const QPointF &pointf, const QVariant &laneInfo);

protected:
    // 悬浮时间
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    QMap<int, RoadPos> m_qmapLaneInfo;
    QMap<int, QPolygonF> m_qmapAllLanePolygon;

private:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void drawPathAndColor(QPainter *&painter, const Painting &filling);
    void drawRoadMark(QPainter *&painter);

    QColor getColor(std::string qstrType);
private:
    std::string m_strRoadId;

    int m_index;
    std::shared_ptr<t_road_lanes_laneSection> m_ptrLaneSection;

    QPolygonF m_qLaneSectionPolygonPoint;

    QMap<std::string, Painting> m_qmapLaneLine;

    QMap<std::string, QPolygonF> m_qmapLanePolygonPoint;

    // none median bidirectional border shoulder stop restricted parking sidewalk biking entry exit driving
    QVector<Painting> m_qvecNoneTypeFilling;
    QVector<Painting> m_qvecMedianTypeFilling;
    QVector<Painting> m_qvecBidirectionalTypeFilling;
    QVector<Painting> m_qvecBorderTypeFilling;
    QVector<Painting> m_qvecShoulderTypeFilling;
    QVector<Painting> m_qvecStopTypeFilling;
    QVector<Painting> m_qvecRestrictedTypeFilling;
    QVector<Painting> m_qvecParkingTypeFilling;
    QVector<Painting> m_qvecSidewalkTypeFilling;
    QVector<Painting> m_qvecBikingTypeFilling;
    QVector<Painting> m_qvecEntryTypeFilling;
    QVector<Painting> m_qvecExitTypeFilling;
    QVector<Painting> m_qvecDrivingTypeFilling;

    QMap<std::string, QColor> m_qmapColor;
};


#endif //ODRVIEWER_LANESECTIONITEM_H
