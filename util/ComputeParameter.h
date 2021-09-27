//
// Created by baijinde on 21-9-23.
//

#ifndef ODRVIEWER_COMPUTEPARAMETER_H
#define ODRVIEWER_COMPUTEPARAMETER_H

#include <vector>
#include <typeinfo>

#include <QPointF>
#include <QPolygonF>
#include <QMetaType>

#include "xodr.h"

typedef struct
{
    QPointF qPointf;
    double dHdg;
}PointFHdg;

struct Painting
{
    QPolygonF polygonF;
    std::string qstrColor;
    std::string qstrStyle;
    double width;
};

struct RoadPos
{
    std::string roadId;
    std::shared_ptr<t_road_lanes_laneSection> laneSection;
    std::shared_ptr<t_road_planView_geometry> geometry;
    std::string laneId;
};

Q_DECLARE_METATYPE(RoadPos)

class ComputeParameter {
public:
    ComputeParameter();
    ~ComputeParameter();

    const QPointF UVToxy(const QPointF &start, const double &dhdg, const double &u, const double &v);
    std::vector<QPointF> getParamPoly3DataPoint(t_road_planView_geometry geometry);

};


#endif //ODRVIEWER_COMPUTEPARAMETER_H
