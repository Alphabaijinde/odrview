//
// Created by baijinde on 21-9-17.
//

#include "MapInfo.h"

#include <QMap>
#include <QPainterPath>

#include <float.h>

//#include "ComputeParameter.h"

#include <stdlib.h>
#include <assert.h>

MapInfo::MapInfo() {}
MapInfo::~MapInfo() {}

int MapInfo::getRoadSurfaceContourPoint(const std::vector< std::shared_ptr<t_road> > &vecAllRoad, RoadMapPoint &roadMapAllPoint)
{
    for(std::shared_ptr<t_road> eachRoad : vecAllRoad)
    {
        double dRoadLength = eachRoad->length._val;
        RoadPoint roadPoint;

        std::map<int, std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>>> mapEachRoadRoadmarkPoint;
        for(int i = 0; i < eachRoad->m_lanes->m_laneSections.size(); ++i)
        {
            LaneSectionPoint laneSectionPoint;
            std::shared_ptr<t_road_lanes_laneSection> eachLaneSection = eachRoad->m_lanes->m_laneSections[i];
            double dLaneStart = eachLaneSection->s._val;
            double dLaneEnd = 0.0;
            int j = i+1;
            for( ; j < eachRoad->m_lanes->m_laneSections.size(); ++j)
            {
                dLaneEnd = eachRoad->m_lanes->m_laneSections[j]->s._val;

                if(true == (fabs(dLaneEnd - dLaneStart) < FLT_EPSILON))
                {
                    continue;
                }
                else
                {
                    break;
                }
            }

            if(j == eachRoad->m_lanes->m_laneSections.size())
            {
                dLaneEnd = dRoadLength;
            }

            // 车道段
            std::shared_ptr<t_road_lanes_laneOffset> eachLaneOffset;
            for(const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset : eachRoad->m_lanes->m_laneOffsets)
            {
                if(laneOffset->s._val > eachLaneSection->s._val)
                {
                    break;
                }

                eachLaneOffset = laneOffset;
            }

            std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>> laneSectionRoadmarkPoint;
            laneSectionPoint = getLaneSectionPoint(eachRoad->id, eachLaneOffset, eachLaneSection, eachRoad->m_planView->m_geometrys, dLaneStart, dLaneEnd, eachRoad->length._val, laneSectionRoadmarkPoint);
            roadPoint.push_back(laneSectionPoint);

            mapEachRoadRoadmarkPoint[i] = laneSectionRoadmarkPoint;
        }

        m_qmapAllRoadMarkPoint[eachRoad->id] = mapEachRoadRoadmarkPoint;
        roadMapAllPoint.push_back(roadPoint);
    }

    return 0;
}

void MapInfo::mergeAllRelativelyLaneSection(QVector<QVector<QPointF> > &qvecQvecEachLaneSection, const QVector<QVector<QVector<QPointF> > > &qvecQvecQvecAllRelativelyLaneSection) const
{
    for(const auto &eachRelativelyLaneSection : qvecQvecQvecAllRelativelyLaneSection)
    {
        for(int i = 0; i < eachRelativelyLaneSection.size(); ++i)
        {
            if (qvecQvecEachLaneSection.size() < eachRelativelyLaneSection.size())
            {
                qvecQvecEachLaneSection.push_back(eachRelativelyLaneSection[i]);
            }
            else
            {
                qvecQvecEachLaneSection[i] += eachRelativelyLaneSection[i];
            }
        }
    }
}

// 车道填充
int MapInfo::getRoadLaneSectionPoint(const RoadMapPoint &roadMapAllPoint, QVector<QVector<QVector<QVector<QPointF> > > > &qvecQvecMapPoint) const
{
    for(int i = 0; i < roadMapAllPoint.size(); ++i)
    {
        // road
        RoadPoint roadPoint = roadMapAllPoint[i];

        QVector<QVector<QVector<QPointF> > >  qvecRoadPoint;

        for(int j = 0; j < roadPoint.size(); ++j)
        {
            // LaneSection
            LaneSectionPoint laneSectionPoint = roadPoint[j];

            QVector<QVector<QVector<QPointF> > > qvecQvecQvecQPointf;
            for(int k = 0; k < laneSectionPoint.size(); ++k)
            {
                // 每一个几何元素的点
                GeometryPoint geometryPoint = laneSectionPoint[k].first;

                if(laneSectionPoint.size() > 1 && k < laneSectionPoint.size() - 1)
                {
                    for(int n = 0; n < geometryPoint.size(); ++n)
                    {
//                        if (geometryPoint[n].size() > NUM_GEOMETRY_ERASE)
//                        {
//                            geometryPoint[n].erase(geometryPoint[n].begin() + geometryPoint[n].size() - NUM_GEOMETRY_ERASE, geometryPoint[n].end());
//                        }
                    }
                }

                QVector<QVector<QPointF> > qvecQvecQPointf; // geometryLength(lanes)
                for(int m = 0; m < geometryPoint.size(); ++m)
                {
                    LanePoint lanePoint = geometryPoint[m];
                    QVector<QPointF> qvecQPointf; // lane
                    for(int n = 0; n < lanePoint.size(); ++n)
                    {
                        qvecQPointf += lanePoint[n].first;
                    }

                    qvecQvecQPointf.push_back(qvecQPointf);
                }

                qvecQvecQvecQPointf.push_back(qvecQvecQPointf);
            }

            // 合并一个车道段所有几何元素的点
            QVector<QVector<QPointF> > eachLaneSection;
            mergeAllRelativelyLaneSection(eachLaneSection, qvecQvecQvecQPointf);

            qvecRoadPoint.push_back(eachLaneSection);
        }

        qvecQvecMapPoint.push_back(qvecRoadPoint);
    }

    return 0;
}

int MapInfo::getRoadGeometryPoint(const RoadMapPoint &roadMapAllPoint, QVector<QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > > &qvecQvecQvecQvecQvecQpointf) const
{
    for(int i = 0; i < roadMapAllPoint.size(); ++i)
    {
        // road
        RoadPoint roadPoint = roadMapAllPoint[i];
        QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > qvecQvecQvecQvecQpointf;

        for(int j = 0; j < roadPoint.size(); ++j)
        {
            LaneSectionPoint laneSectionPoint = roadPoint[j];
            QVector<std::pair<QVector<QVector<QPointF> >, int> > qvecQvecQvecQpointf;

            for(int k = 0; k < laneSectionPoint.size(); ++k)
            {
                GeometryPoint geometryPoint = laneSectionPoint[k].first;
                QVector<QVector<QPointF> > qvecQvecQpointf;

                for(int m = 0; m < geometryPoint.size(); ++m)
                {
                    LanePoint lanePoint = geometryPoint[m];
                    QVector<QPointF> qvecQpointf;

                    for(int n = 0; n < lanePoint.size(); ++n)
                    {
                        qvecQpointf.push_back(lanePoint[n].first);
                    }

                    qvecQvecQpointf.push_back(qvecQpointf);
                }

                qvecQvecQvecQpointf.push_back(std::make_pair(qvecQvecQpointf, laneSectionPoint[k].second));
            }

            qvecQvecQvecQvecQpointf.push_back(qvecQvecQvecQpointf);
        }

        qvecQvecQvecQvecQvecQpointf.push_back(qvecQvecQvecQvecQpointf);
    }

    return 0;
}

int MapInfo::getAllRoadMarkPoint(std::map<std::string, std::map<int, std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>>>> &allRoadMarkPoint)
{
    allRoadMarkPoint = m_qmapAllRoadMarkPoint;
    return 0;
}

LaneSectionPoint MapInfo::getLaneSectionPoint(const std::string& roadId, const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset, const std::shared_ptr<t_road_lanes_laneSection> &laneSection, const std::vector<std::shared_ptr<t_road_planView_geometry>> &vecGeometry, double dLaneSectionStart, double dLaneSectionEnd, double dRoadLength, std::map<int, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>>> &lanesectionRoadmarkPoint)
{
    // 获取当前车道段所在几何元素的起止区间
    LaneSectionPoint laneSectionPoint;
    if(dLaneSectionStart > dLaneSectionEnd)
    {
        return laneSectionPoint;
    }

    int I,J;
    getGeometryIndex(roadId, vecGeometry, I, J, dLaneSectionStart, dLaneSectionEnd);

    if(I < 0 || J < 0)
    {
        return laneSectionPoint;
    }

    double dRelatGeoStart, dRelatGeoEnd;
    for (int k = I; k <= J; ++k)
    {
        std::vector<QVector<std::pair<QPointF, int> > > qvecQvecEachRelativelyLaneSection;
        std::shared_ptr<t_road_planView_geometry> eachGeometry = vecGeometry[k];

        if (0 == (J - I))
        {
            dRelatGeoStart = dLaneSectionStart - eachGeometry->s._val;
            dRelatGeoEnd = dLaneSectionEnd - eachGeometry->s._val;
        }
        else if (1 <= (J - I))
        {
            if (k == I)
            {
                dRelatGeoStart = dLaneSectionStart - eachGeometry->s._val;
                dRelatGeoEnd = eachGeometry->length._val;
            }
            else if (k == J)
            {
                dRelatGeoStart = 0;
                dRelatGeoEnd = dLaneSectionEnd - eachGeometry->s._val;
            }
            else
            {
                dRelatGeoStart = 0;
                dRelatGeoEnd = eachGeometry->length._val;
            }
        }
        else
        {
            assert("other case");
        }

        std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>> laneRoadmarkPoint;
        // 车道段对应的几何元素
        qvecQvecEachRelativelyLaneSection = getGeometryData(laneOffset, laneSection, eachGeometry, dRelatGeoStart, dRelatGeoEnd, dLaneSectionEnd, dRoadLength, laneRoadmarkPoint);
        laneSectionPoint.push_back(std::make_pair(qvecQvecEachRelativelyLaneSection, k));

        lanesectionRoadmarkPoint[k] = laneRoadmarkPoint;
    }

    return laneSectionPoint;
}

std::vector<QVector<std::pair<QPointF, int> > > MapInfo::getGeometryData(const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset, const std::shared_ptr<t_road_lanes_laneSection> &laneSection, const std::shared_ptr<t_road_planView_geometry> &geometry, double dRelatGeometrySStart, double dRelatGeometrySEnd, double dLaneSectionEnd, double dRoadLength, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int>>>> &laneRoadmarkPoint)
{
    // 地理几何元素s 减 车道段s，得到相对车道段起始点的距离
    // 如果几何元素距离大于车道段距离，以几何元素的相对值为起始
    // 如果几何元素距离小于车道段距离，以车道段的相对值为起始
    double dRelatLaneSectionSOffset = 0.0;
    if (geometry->s._val > laneSection->s._val)
    {
        dRelatLaneSectionSOffset = geometry->s._val - laneSection->s._val;
    }

    QVector<std::pair<QPointF, int> > qvecQpointf;
    std::vector< QVector<std::pair<QPointF, int> > > qvecQvecCenterLanePoint;
    std::map<int, QVector<std::pair<QPointF, int> > > qvecQvecLeftLanesPoint;
    std::map<int, QVector<std::pair<QPointF, int> > > qvecQvecRightLanesPoint;
    // 相对几何的s
    // 相对车道段的s dSOffset + ds;
    // road的绝对s  laneOffset.s + dSOffset + ds;
    int iStep = 2;
    if((dRelatGeometrySEnd - dRelatGeometrySStart) / 100000000000 > 1)
    {
        iStep = 1000000000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 10000000000 > 1)
    {
        iStep = 100000000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 1000000000 > 1)
    {
        iStep = 10000000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 100000000 > 1)
    {
        iStep = 1000000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 10000000 > 1)
    {
        iStep = 100000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 1000000 > 1)
    {
        iStep = 10000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 100000 > 1)
    {
        iStep = 1000;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 10000 > 1)
    {
        iStep = 100;
    }
    else if((dRelatGeometrySEnd - dRelatGeometrySStart) / 1000 > 1)
    {
        iStep = 10;
    }

    std::vector<double> vecRoadMarks;
    for(double ds = dRelatGeometrySStart; ds < dRelatGeometrySEnd; ds += iStep)
    {
        if(ds > 0)
        {
            for(double dRoadMarkS = ds - 1; dRoadMarkS > ds - iStep; dRoadMarkS -= 1)
            {
                vecRoadMarks.insert(vecRoadMarks.begin(), dRoadMarkS);
            }
        }

        getAllPointOfLaneFromGeometryS(geometry, laneOffset, laneSection, ds, dRelatGeometrySStart, dLaneSectionEnd, dRelatLaneSectionSOffset, dRoadLength,
                                       vecRoadMarks, qvecQpointf, qvecQvecLeftLanesPoint, qvecQvecRightLanesPoint, laneRoadmarkPoint);

        vecRoadMarks.clear();
    }

    getAllPointOfLaneFromGeometryS(geometry, laneOffset, laneSection, dRelatGeometrySEnd, dRelatGeometrySStart, dLaneSectionEnd, dRelatLaneSectionSOffset, dRoadLength,
                                   vecRoadMarks, qvecQpointf, qvecQvecLeftLanesPoint, qvecQvecRightLanesPoint, laneRoadmarkPoint);

    qvecQvecCenterLanePoint.push_back(qvecQpointf);

    // 调整顺序和车道顺序一致
    std::vector<QVector<std::pair<QPointF, int> > > qvecQvecAllLanesPoint;
    pointfOfLanesOrderAdjust(qvecQvecAllLanesPoint, qvecQvecCenterLanePoint,
                            qvecQvecLeftLanesPoint, qvecQvecRightLanesPoint);

    return qvecQvecAllLanesPoint;
}

void MapInfo::pointfOfLanesOrderAdjust(std::vector<QVector<std::pair<QPointF, int> > > &vecQvecAllLanesPoint,
                              const std::vector< QVector<std::pair<QPointF, int> > > &vecQvecCenterLanePoint,
                              const std::map<int, QVector<std::pair<QPointF, int> > > &vecQvecLeftLanesPoint,
                              const std::map<int, QVector<std::pair<QPointF, int> > > &vecQvecRightLanesPoint
                              ) const
{
    for (int i = 0; i < vecQvecLeftLanesPoint.size(); ++i)
    {
        vecQvecAllLanesPoint.push_back(vecQvecLeftLanesPoint.at(i));
    }

    vecQvecAllLanesPoint.push_back(vecQvecCenterLanePoint[0]);

    for (int j = 0; j < vecQvecRightLanesPoint.size(); ++j)
    {
        vecQvecAllLanesPoint.push_back(vecQvecRightLanesPoint.at(j));
    }
}

void MapInfo::getLengthOfRoadMarkFromLane(std::vector<double> &vecRoadMarkLength, const t_road_lanes_laneSection_lr_lane &eachLane, const double &dLaneSectionEnd) const
{
    for(int j = 0; j < eachLane.m_roadMarks.size(); ++j)
    {
        if(j+1 == eachLane.m_roadMarks.size())
        {
            vecRoadMarkLength.push_back(dLaneSectionEnd);
        }
        else
        {
            vecRoadMarkLength.push_back(eachLane.m_roadMarks[j+1]->sOffset._val);
        }
    }
}

PointFHdg MapInfo::getLineData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    PointFHdg pointfHdg;
    pointfHdg.qPointf = QPointF(geometry->x, geometry->y) + QPointF(dPos * cos(geometry->hdg), dPos * sin(geometry->hdg));
    pointfHdg.dHdg = geometry->hdg;

    return pointfHdg;
}

PointFHdg MapInfo::getSpiralData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    EulerSpiral eulerSpiral = EulerSpiral::createFromLengthAndCurvature(geometry->length._val, geometry->m_t_road_planView_geometry->m_spiral->curvStart, geometry->m_t_road_planView_geometry->m_spiral->curvEnd);
    return eulerSpiral.calc(dPos, geometry->x, geometry->y, geometry->m_t_road_planView_geometry->m_spiral->curvStart, geometry->hdg);
}

PointFHdg MapInfo::getArcData(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    double c = geometry->m_t_road_planView_geometry->m_arc->curvature;
    double dHeading = geometry->hdg - M_PI / 2;

    double a = 2 / c * sin(dPos * c / 2);
    double alpha = (M_PI - dPos * c) / 2 - dHeading;

    double dx = -1 * a * cos(alpha);
    double dy = a * sin(alpha);

    PointFHdg pointfHdg;
    pointfHdg.qPointf = QPointF(geometry->x, geometry->y) + QPointF(dx, dy);
    pointfHdg.dHdg = geometry->hdg + dPos *  c;

    return pointfHdg;
}

PointFHdg MapInfo::getPoly3Data(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    double t = geometry->m_t_road_planView_geometry->m_poly3->a + geometry->m_t_road_planView_geometry->m_poly3->b * pow(dPos, 1) +
               geometry->m_t_road_planView_geometry->m_poly3->c * pow(dPos, 2) + geometry->m_t_road_planView_geometry->m_poly3->d * pow(dPos, 3);

    double srot = dPos * cos(geometry->hdg) - t * sin(geometry->hdg);
    double trot = dPos * sin(geometry->hdg) + t * cos(geometry->hdg);

    double tangent = 1 * geometry->m_t_road_planView_geometry->m_poly3->b + 2 * geometry->m_t_road_planView_geometry->m_poly3->c * pow(dPos, 1) + 3 * geometry->m_t_road_planView_geometry->m_poly3->d * pow(dPos, 2);

    PointFHdg pointfHdg;
    pointfHdg.qPointf = QPointF(geometry->x, geometry->y) + QPointF(srot, trot);
    pointfHdg.dHdg = geometry->hdg + atan2(tangent, 1.0);

    return pointfHdg;
}

PointFHdg MapInfo::getParamPoly3Data(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    std::vector<QPointF> vec = ComputeParameter().getParamPoly3DataPoint(*geometry.get());
    QPointF start           = vec[0];
    QPointF lControllPoint  = vec[1];
    QPointF RControllPoint  = vec[2];
    QPointF end             = vec[3];

    QPainterPath path;
    path.moveTo(start);
    path.cubicTo(lControllPoint, RControllPoint, end);
    double pos = path.percentAtLength(dPos);

    if(geometry->m_t_road_planView_geometry->m_paramPoly3->pRange == e_paramPoly3_pRange::ARCLENGTH)
    {
        pos *= geometry->length._val;
    }

    double x = geometry->m_t_road_planView_geometry->m_paramPoly3->aU + geometry->m_t_road_planView_geometry->m_paramPoly3->bU * pow(pos, 1) +
                geometry->m_t_road_planView_geometry->m_paramPoly3->cU * pow(pos, 2) + geometry->m_t_road_planView_geometry->m_paramPoly3->dU * pow(pos, 3);

    double y = geometry->m_t_road_planView_geometry->m_paramPoly3->aV + geometry->m_t_road_planView_geometry->m_paramPoly3->bV * pow(pos, 1) +
                geometry->m_t_road_planView_geometry->m_paramPoly3->cV * pow(pos, 2) + geometry->m_t_road_planView_geometry->m_paramPoly3->dV * pow(pos, 3);

    double xrot = x * cos(geometry->hdg) - y * sin(geometry->hdg);
    double yrot = x * sin(geometry->hdg) + y * cos(geometry->hdg);

    double dx = 1 * geometry->m_t_road_planView_geometry->m_paramPoly3->bU + 2 * geometry->m_t_road_planView_geometry->m_paramPoly3->cU * pow(pos, 1) + 3 * geometry->m_t_road_planView_geometry->m_paramPoly3->dU * pow(pos, 2);
    double dy = 1 * geometry->m_t_road_planView_geometry->m_paramPoly3->bV + 2 * geometry->m_t_road_planView_geometry->m_paramPoly3->cV * pow(pos, 1) + 3 * geometry->m_t_road_planView_geometry->m_paramPoly3->dV * pow(pos, 2);

    //double tangent = atan(tan(dy/dx));
    double tangent = atan2(dy, dx);

    PointFHdg pointfHdg;
    pointfHdg.qPointf = QPointF(geometry->x, geometry->y) + QPointF(xrot, yrot);
    pointfHdg.dHdg = geometry->hdg + tangent;

    return pointfHdg;
}

PointFHdg MapInfo::calcPosition(const std::shared_ptr<t_road_planView_geometry> &geometry, double dPos) const
{
    if (geometry->m_t_road_planView_geometry->m_line.get() != nullptr)
    {
        return getLineData(geometry, dPos);
    }
    else if (geometry->m_t_road_planView_geometry->m_spiral.get() != nullptr)
    {
        return getSpiralData(geometry, dPos);
    }
    else if (geometry->m_t_road_planView_geometry->m_arc.get() != nullptr)
    {
        return getArcData(geometry, dPos);
    }
    else if (geometry->m_t_road_planView_geometry->m_poly3.get() != nullptr)
    {
        return getPoly3Data(geometry, dPos);
    }
    else if (geometry->m_t_road_planView_geometry->m_paramPoly3.get() != nullptr)
    {
        return getParamPoly3Data(geometry, dPos);
    }

    return PointFHdg();
}

void MapInfo::getReferenceOffset(PointFHdg &pointfHdg, const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset, const double dLaneSectionDs) const
{
    double dLaneOffset = 0.0;
    if(laneOffset)
    {
        dLaneOffset = laneOffset->a + laneOffset->b * dLaneSectionDs + laneOffset->c * pow(dLaneSectionDs, 2) + laneOffset->d * pow(dLaneSectionDs, 3);
    }

    pointfHdg.qPointf.setX(pointfHdg.qPointf.rx() - dLaneOffset * sin(pointfHdg.dHdg));
    pointfHdg.qPointf.setY(pointfHdg.qPointf.ry() + dLaneOffset * cos(pointfHdg.dHdg));
}

PointFHdg MapInfo::getReferencePointf(const std::shared_ptr<t_road_planView_geometry> &geometry, const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                             const double &dGeometryS, const double &dRelatLaneSectionS) const
{
    // 获取s位置处的坐标Pos和航向heading
    PointFHdg pointfHdg = calcPosition(geometry, dGeometryS);

    // 参考线偏移(使用车道段的距离)
    getReferenceOffset(pointfHdg, laneOffset, dRelatLaneSectionS);

    return pointfHdg;
}

int MapInfo::getIndexOfVec(const std::vector<double> &vec, const double &dRelatSectionDS) const
{
    for(int j = 0; j < (int)vec.size(); ++j)
    {
        if(dRelatSectionDS < vec[j] || fabs(dRelatSectionDS - vec[j]) < FLT_EPSILON)
        {
            return j;
        }
    }

    return -1;
}

//符号函数的定义,传入一个变量,如果变量为正数,返回1;如果变量为负数,返回-1;如果变量为0,返回0
double sgn(double dSgnVar) // 不好用后期修改
{
    double dSgnValue;

    if (dSgnVar > 0.0)
    {
        dSgnValue = 1;
    }
    else if (dSgnVar < 0.0)
    {
        dSgnValue = -1;
    }
    else if (dSgnVar <= std::numeric_limits<double>::epsilon() && dSgnVar >= -std::numeric_limits<double>::epsilon())
    {
        dSgnValue = 0;
    }
    else
    {
        assert("MapInfo::sgn error case");
    }

    return -dSgnValue;
}

void MapInfo::genRoadMarkPointf(QPointF qpointf, double hdg, int iIndexRoadMark, double dRelatLaneSectionS, double dLengthToReferenc, const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> &qvecLane, int iLaneIndex, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint)
{
    // 增加条件iIndexRoadMark < 0 ,请晋德帮忙看看 王闯 2021-07-16
    if(qvecLane[iLaneIndex]->m_roadMarks.empty() || iIndexRoadMark < 0)
    {
        return;
    }

    int iLaneId = 0;
    if(dynamic_cast<t_road_lanes_laneSection_left_lane *>(qvecLane[iLaneIndex].get()) != nullptr)
    {
        iLaneId = dynamic_cast<t_road_lanes_laneSection_left_lane *>(qvecLane[iLaneIndex].get())->id;
    }
    else if(dynamic_cast<t_road_lanes_laneSection_center_lane *>(qvecLane[iLaneIndex].get()) != nullptr)
    {
        iLaneId = dynamic_cast<t_road_lanes_laneSection_center_lane *>(qvecLane[iLaneIndex].get())->id;
    }
    else if(dynamic_cast<t_road_lanes_laneSection_right_lane *>(qvecLane[iLaneIndex].get()) != nullptr)
    {
        iLaneId = dynamic_cast<t_road_lanes_laneSection_right_lane *>(qvecLane[iLaneIndex].get())->id;
    }

    std::string strLaneId = std::to_string(iLaneId);

    if(e_roadMarkType::NONE == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
    }
    else if(e_roadMarkType::SOLID == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        if(iIndexRoadMark >= 1 && qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type != qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark - 1]->type && laneRoadmarkPoint[strLaneId]["center"].size() > 0)
        {
            laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(laneRoadmarkPoint[strLaneId]["center"].last().first, iIndexRoadMark);
        }
        else
        {
            if((laneRoadmarkPoint[strLaneId]["center"].size() > 0) && (laneRoadmarkPoint[strLaneId]["center"].last().second >= 0) && (laneRoadmarkPoint[strLaneId]["center"].last().second != iIndexRoadMark))
            {
                laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(laneRoadmarkPoint[strLaneId]["center"].last().first, iIndexRoadMark);
            }
        }

        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, iIndexRoadMark);
    }
    else if(e_roadMarkType::BROKEN == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        // 白色虚线 >=60km/h 600cm 900cm <60km/h 200cm 400cm
        // 先虚再实 450---600---900---600
        if(dRelatLaneSectionS - qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val <= 4.5)
        {
            laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
        }
        else if(fmod((dRelatLaneSectionS-qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val - 4.5), 15.0) >= 6.0)
        {
            laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
        }
        else
        {
            laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, iIndexRoadMark); // 实
        }
    }
    else if(e_roadMarkType::SOLID_SOLID == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        int iSgn = sgn(QString(strLaneId.c_str()).toDouble());
        if(iSgn == 0)
        {
            iSgn = 1;
        }

        if(iIndexRoadMark >= 1 && qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type != qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark - 1]->type && !laneRoadmarkPoint[strLaneId]["center"].empty())
        {
            QPointF leftqpointf;

            leftqpointf.setX(laneRoadmarkPoint[strLaneId]["center"].last().first.x() - iSgn * (-0.15) * sin(hdg));

            leftqpointf.setY(laneRoadmarkPoint[strLaneId]["center"].last().first.y() + iSgn * (-0.15) * cos(hdg));

            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);
        }
        else
        {
            if(!laneRoadmarkPoint[strLaneId]["left"].empty() && (laneRoadmarkPoint[strLaneId]["left"].last().second >= 0) && (laneRoadmarkPoint[strLaneId]["left"].last().second != iIndexRoadMark))
            {
                laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(laneRoadmarkPoint[strLaneId]["left"].last().first, iIndexRoadMark);
            }
        }

        QPointF leftqpointf;
        leftqpointf.setX(qpointf.x() - iSgn * (-0.15) * sin(hdg));
        leftqpointf.setY(qpointf.y() + iSgn * (-0.15) * cos(hdg));

        laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);

        if(iIndexRoadMark >= 1 && qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type != qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark - 1]->type && laneRoadmarkPoint[strLaneId]["center"].size() > 0)
        {
            QPointF rightqpointf;
            rightqpointf.setX(laneRoadmarkPoint[strLaneId]["center"].last().first.x() - iSgn * 0.15 * sin(hdg));
            rightqpointf.setY(laneRoadmarkPoint[strLaneId]["center"].last().first.y() + iSgn * 0.15 * cos(hdg));

            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);
        }
        else
        {
            if((laneRoadmarkPoint[strLaneId]["right"].size() > 0) && (laneRoadmarkPoint[strLaneId]["right"].last().second >= 0) && (laneRoadmarkPoint[strLaneId]["right"].last().second != iIndexRoadMark))
            {
                laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(laneRoadmarkPoint[strLaneId]["right"].last().first, iIndexRoadMark);
            }
        }

        QPointF rightqpointf;
        rightqpointf.setX(qpointf.x() - iSgn * 0.15 * sin(hdg));
        rightqpointf.setY(qpointf.y() + iSgn * 0.15 * cos(hdg));

        laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);

        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
    }
    else if(e_roadMarkType::SOLID_BROKEN == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        int iSgn = sgn(QString(strLaneId.c_str()).toDouble());
        if(iSgn == 0)
        {
            iSgn = 1;
        }

        if(iIndexRoadMark >= 1 && qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type != qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark - 1]->type && laneRoadmarkPoint[strLaneId]["center"].size() > 0)
        {
            QPointF leftqpointf;
            leftqpointf.setX(laneRoadmarkPoint[strLaneId]["center"].last().first.x() - iSgn * (-0.15) * sin(hdg));
            leftqpointf.setY(laneRoadmarkPoint[strLaneId]["center"].last().first.y() + iSgn * (-0.15) * cos(hdg));

            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);
        }
        else
        {
            if((laneRoadmarkPoint[strLaneId]["left"].size() > 0) && (laneRoadmarkPoint[strLaneId]["left"].last().second >= 0) && (laneRoadmarkPoint[strLaneId]["left"].last().second != iIndexRoadMark))
            {
                laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(laneRoadmarkPoint[strLaneId]["left"].last().first, iIndexRoadMark);
            }
        }

        QPointF leftqpointf;
        leftqpointf.setX(qpointf.x() - iSgn * (-0.15) * sin(hdg));
        leftqpointf.setY(qpointf.y() + iSgn * (-0.15) * cos(hdg));

        laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);

        QPointF rightqpointf;
        rightqpointf.setX(qpointf.x() - iSgn * 0.15 * sin(hdg));
        rightqpointf.setY(qpointf.y() + iSgn * 0.15 * cos(hdg));

        if(dRelatLaneSectionS - qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val <= 4.5)
        {
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, -1);
        }
        else if(fmod((dRelatLaneSectionS - qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val - 4.5), 15.0) >= 6.0)
        {
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, -1);
        }
        else
        {
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);
        }

        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
    }
    else if(e_roadMarkType::BROKEN_SOLID == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        int iSgn = sgn(QString(strLaneId.c_str()).toDouble());
        if(iSgn == 0)
        {
            iSgn = 1;
        }

        QPointF leftqpointf;
        leftqpointf.setX(qpointf.x() - iSgn * (-0.15) * sin(hdg));
        leftqpointf.setY(qpointf.y() + iSgn * (-0.15) * cos(hdg));

        if(dRelatLaneSectionS-qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val <= 4.5)
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, -1);
        }
        else if(fmod((dRelatLaneSectionS-qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val - 4.5), 15.0) >= 6.0)
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, -1);
        }
        else
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);
        }

        if(iIndexRoadMark >= 1 && qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type != qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark - 1]->type && laneRoadmarkPoint[strLaneId]["center"].size() > 0)
        {
            QPointF rightqpointf;
            rightqpointf.setX(laneRoadmarkPoint[strLaneId]["center"].last().first.x() - iSgn * 0.15 * sin(hdg));
            rightqpointf.setY(laneRoadmarkPoint[strLaneId]["center"].last().first.y() + iSgn * 0.15 * cos(hdg));

            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);
        }
        else
        {
            if((laneRoadmarkPoint[strLaneId]["right"].size() > 0) && (laneRoadmarkPoint[strLaneId]["right"].last().second >= 0) && (laneRoadmarkPoint[strLaneId]["right"].last().second != iIndexRoadMark))
            {
                laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(laneRoadmarkPoint[strLaneId]["right"].last().first, iIndexRoadMark);
            }
        }

        QPointF rightqpointf;
        rightqpointf.setX(qpointf.x() - iSgn * 0.15 * sin(hdg));
        rightqpointf.setY(qpointf.y() + iSgn * 0.15 * cos(hdg));

        laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);

        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
    }
    else if(e_roadMarkType::BROKEN_BROKEN == qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->type)
    {
        int iSgn = sgn(QString(strLaneId.c_str()).toDouble());
        if(iSgn == 0)
        {
            iSgn = 1;
        }

        QPointF leftqpointf;
        leftqpointf.setX(qpointf.x() - iSgn * (-0.15) * sin(hdg));
        leftqpointf.setY(qpointf.y() + iSgn * (-0.15) * cos(hdg));

        QPointF rightqpointf;
        rightqpointf.setX(qpointf.x() - iSgn * 0.15 * sin(hdg));
        rightqpointf.setY(qpointf.y() + iSgn * 0.15 * cos(hdg));

        if(dRelatLaneSectionS-qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val <= 4.5)
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, -1);
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, -1);
        }
        else if(fmod((dRelatLaneSectionS-qvecLane[iLaneIndex]->m_roadMarks[iIndexRoadMark]->sOffset._val - 4.5), 15.0) >= 6.0)
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, -1);
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, -1);
        }
        else
        {
            laneRoadmarkPoint[strLaneId]["left"] += std::make_pair(leftqpointf, iIndexRoadMark);
            laneRoadmarkPoint[strLaneId]["right"] += std::make_pair(rightqpointf, iIndexRoadMark);
        }

        laneRoadmarkPoint[strLaneId]["center"] += std::make_pair(qpointf, -1);
    }
    else
    {
        assert("暂时没有实现");
    }
}

void MapInfo::getLengthOfWidthFromLane(std::vector<double> &vecWidthLength, std::map<double, int> &mapWidthLengthAndIndex, const std::shared_ptr<t_road_lanes_laneSection_lr_lane> eachLane, const double &dLaneSectionEnd) const
{
    std::vector<std::pair<std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>, int>> vecWidth;
    for(int j = 0; j < eachLane->m_t_road_lanes_laneSection_lr_lanes.size(); ++j)
    {
        if(!eachLane->m_t_road_lanes_laneSection_lr_lanes.at(j)->m_widths.empty())
        {
            vecWidth.push_back(std::make_pair(eachLane->m_t_road_lanes_laneSection_lr_lanes.at(j)->m_widths[0], j));
        }
    }

    for(int j = 0; j < vecWidth.size(); ++j)
    {
        if(j+1 == vecWidth.size())
        {
            vecWidthLength.push_back(dLaneSectionEnd);
            mapWidthLengthAndIndex.emplace(dLaneSectionEnd, vecWidth[j].second);
        }
        else
        {
            vecWidthLength.push_back(vecWidth[j+1].first->sOffset._val);
            mapWidthLengthAndIndex.emplace(vecWidth[j+1].first->sOffset._val, vecWidth[j].second);
        }
    }
}

std::shared_ptr<t_road_lanes_laneSection_lr_lane_width> MapInfo::getWidthFromLane(const std::shared_ptr<t_road_lanes_laneSection_lr_lane> lane, const double &dLaneSectionEnd, const double &dRelatSectionDS) const
{
    // 将当前Width的s区间放入数组
    // 生成查询s对应的Width的区间数组
    std::vector<double> vecWidthLength;
    std::map<double, int> mapWidthLengthAndIndex;
    getLengthOfWidthFromLane(vecWidthLength, mapWidthLengthAndIndex, lane, dLaneSectionEnd);
    // 获取当前s对应的Width
    int iIndex = getIndexOfVec(vecWidthLength, dRelatSectionDS);
    if(-1 == iIndex)
    {
        return std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>();
    }


    return lane->m_t_road_lanes_laneSection_lr_lanes[mapWidthLengthAndIndex[vecWidthLength[iIndex]]]->m_widths[0];
}

std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>> MapInfo::getAllWidthToReference(const int iLaneIndex, const double &dLaneSectionEnd, const double &dLaneSectionDs, const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> &vecLane, bool isLeft) const
{
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>> qvecWidth;

    if(!isLeft)
    {
        for(int j = 0; j <= iLaneIndex; ++j) // 负车道
        {
            // 获取每条车道当前s对应的Width
            qvecWidth.push_back(getWidthFromLane(vecLane[j], dLaneSectionEnd, dLaneSectionDs));
        }
    }
    else
    {
        for(int j = vecLane.size() - 1; j >= iLaneIndex; --j) // 正车道
        {
            // 获取每条车道当前s对应的Width
            qvecWidth.push_back(getWidthFromLane(vecLane[j], dLaneSectionEnd, dLaneSectionDs));
        }
    }

    return qvecWidth;
}

// 通过车道id和s获取当前车道到参考线正交位置的距离(此处非零的可以叠加)
double MapInfo::getDistanceFromCurrentLaneAndS(const int iLaneIndex, const double &dLaneSectionEnd, const double &dLaneSectionDs, const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> &vecLane, bool isLeft) const
{
    // 获取当前车道到基准线的所有Width
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane_width>> vecWidth = getAllWidthToReference(iLaneIndex, dLaneSectionEnd, dLaneSectionDs, vecLane, isLeft);

    double dLengthToReferenc = 0;
    for(auto eachWidth : vecWidth)
    {
        double dRelatWidthDs = dLaneSectionDs - eachWidth->sOffset._val;
        dLengthToReferenc += eachWidth->a + eachWidth->b * pow(dRelatWidthDs, 1) +
                eachWidth->c * pow(dRelatWidthDs, 2) + eachWidth->d * pow(dRelatWidthDs, 3);
    }

    return dLengthToReferenc;
}

// 按roadMark放置代码
QVector<std::pair<QPointF, int> > MapInfo::getCurrentLanePoint(const std::shared_ptr<t_road_planView_geometry> &geometry, const PointFHdg &pointfHdg, const int iLaneIndex, const double dLaneSectionEnd, const double dRelatLaneSectionS, const double dRelatRoadS, const double dRoadLength, const std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> &qvecLane, const std::vector<std::pair<double, PointFHdg>> &qvecRelatLaneSectionSAndPointFHdg, std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint, bool isLeft)
{
    Q_UNUSED(geometry);

    double dLaneId = 0.0;
    if(dynamic_cast<t_road_lanes_laneSection_left_lane *>(qvecLane[iLaneIndex].get()) != nullptr)
    {
        dLaneId = dynamic_cast<t_road_lanes_laneSection_left_lane *>(qvecLane[iLaneIndex].get())->id;
    }
    else if(dynamic_cast<t_road_lanes_laneSection_right_lane *>(qvecLane[iLaneIndex].get()) != nullptr)
    {
        dLaneId = dynamic_cast<t_road_lanes_laneSection_right_lane *>(qvecLane[iLaneIndex].get())->id;
    }
    else
    {
        assert("no center");
    }

    int iSgn = sgn(dLaneId);

    // 获取当前位置对应的roadMark索引
    // 将当前RoadMark的s区间放入数组
    // 生成查询s对应的RoadMark的区间数组
    std::vector<double> vecRoadMarkLength;
    getLengthOfRoadMarkFromLane(vecRoadMarkLength, *qvecLane[iLaneIndex], dLaneSectionEnd);

    for(int i = 0; i < qvecRelatLaneSectionSAndPointFHdg.size(); ++i)
    {
        // TODO 和宽度的偏移量不一致，需要考虑宽度变化区间
        double dAddLengthToReferenc = getDistanceFromCurrentLaneAndS(iLaneIndex, dLaneSectionEnd, qvecRelatLaneSectionSAndPointFHdg[i].first, qvecLane, isLeft);

        int iAddIndexRoadMark = getIndexOfVec(vecRoadMarkLength, qvecRelatLaneSectionSAndPointFHdg[i].first);

        QPointF qAddPointf;
        qAddPointf.setX(qvecRelatLaneSectionSAndPointFHdg[i].second.qPointf.x() - iSgn * dAddLengthToReferenc * sin(qvecRelatLaneSectionSAndPointFHdg[i].second.dHdg));
        qAddPointf.setY(qvecRelatLaneSectionSAndPointFHdg[i].second.qPointf.y() + iSgn * dAddLengthToReferenc * cos(qvecRelatLaneSectionSAndPointFHdg[i].second.dHdg));

        // 车道线的点
        genRoadMarkPointf(qAddPointf, qvecRelatLaneSectionSAndPointFHdg[i].second.dHdg, iAddIndexRoadMark, qvecRelatLaneSectionSAndPointFHdg[i].first, dAddLengthToReferenc, qvecLane, iLaneIndex, laneRoadmarkPoint);
    }

    double dLengthToReferenc = getDistanceFromCurrentLaneAndS(iLaneIndex, dLaneSectionEnd, dRelatLaneSectionS, qvecLane, isLeft);

    // 道路的点
    QPointF qpointf;
    qpointf.setX(pointfHdg.qPointf.x() - iSgn * dLengthToReferenc * sin(pointfHdg.dHdg));
    qpointf.setY(pointfHdg.qPointf.y() + iSgn * dLengthToReferenc * cos(pointfHdg.dHdg));

    QVector<std::pair<QPointF, int> > qvecRoadPoint;
    // 获取当前s对应的RoadMark
    int iIndexRoadMark = getIndexOfVec(vecRoadMarkLength, dRelatLaneSectionS);
    qvecRoadPoint.push_back(std::make_pair(qpointf, iIndexRoadMark));

    // 车道线的点
    genRoadMarkPointf(qpointf, pointfHdg.dHdg, iIndexRoadMark, dRelatLaneSectionS, dLengthToReferenc, qvecLane, iLaneIndex, laneRoadmarkPoint);

    return qvecRoadPoint;
}

void MapInfo::getAllPointOfLaneFromGeometryS(const std::shared_ptr<t_road_planView_geometry> &geometry,
                                    const std::shared_ptr<t_road_lanes_laneOffset> &laneOffset,
                                    const std::shared_ptr<t_road_lanes_laneSection> &laneSection,
                                    const double &dGeometryS, const double &dRelatGeometrySStart,
                                    const double &dLaneSectionEnd, const double &dRelatLaneSectionSOffset,
                                    const double &dRoadLength,
                                    const std::vector<double> &vecRoadMarkS,
                                    QVector<std::pair<QPointF, int> > &vecQpointf,
                                    std::map<int, QVector<std::pair<QPointF, int> > > &qvecQvecLeftLanesPoint,
                                    std::map<int, QVector<std::pair<QPointF, int> > > &qvecQvecRightLanesPoint,
                                    std::map<std::string, std::map<std::string, QVector<std::pair<QPointF, int> > > > &laneRoadmarkPoint)
{
    std::vector<double> vecRoadMarkLength;
    std::vector<std::pair<double, PointFHdg>> qvecRelatLaneSectionSAndPointFHdg;
    // 车道标线补充点
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> centerLanes;

    if(laneSection->m_center)
    {
        getLengthOfRoadMarkFromLane(vecRoadMarkLength, *(dynamic_cast<t_road_lanes_laneSection_lr_lane *>(laneSection->m_center->m_lanes[0].get())), dLaneSectionEnd);

        for(auto eachLane : laneSection->m_center->m_lanes)
        {
            centerLanes.push_back(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
        }
    }

    for(int i = 0; i < vecRoadMarkS.size(); ++i)
    {
        double dAddRelatLaneSectionS = vecRoadMarkS[i] - dRelatGeometrySStart + dRelatLaneSectionSOffset; // 相对车道段的S
        // 中心车道
        PointFHdg addPointfHdg = getReferencePointf(geometry, laneOffset, vecRoadMarkS[i], dAddRelatLaneSectionS);

        int iAddIndexRoadMark = getIndexOfVec(vecRoadMarkLength, dAddRelatLaneSectionS);

        genRoadMarkPointf(addPointfHdg.qPointf, addPointfHdg.dHdg, iAddIndexRoadMark, dAddRelatLaneSectionS, 0, centerLanes, 0, laneRoadmarkPoint);

        qvecRelatLaneSectionSAndPointFHdg.push_back(std::make_pair(dAddRelatLaneSectionS, addPointfHdg));
    }

    double dRelatLaneSectionS = dGeometryS - dRelatGeometrySStart + dRelatLaneSectionSOffset; // 相对车道段的S
    double dRelatRoadS = dRelatLaneSectionS + laneSection->s._val; // 相对道路的S

    // 中心车道
    int iIndexRoadMark = getIndexOfVec(vecRoadMarkLength, dRelatLaneSectionS);

    PointFHdg pointfHdg = getReferencePointf(geometry, laneOffset, dGeometryS, dRelatLaneSectionS);
    vecQpointf.push_back(std::make_pair(pointfHdg.qPointf, iIndexRoadMark));

    genRoadMarkPointf(pointfHdg.qPointf, pointfHdg.dHdg, iIndexRoadMark, dRelatLaneSectionS, 0, centerLanes, 0, laneRoadmarkPoint);

    m_dCurLengthToReferenc = 0.0;
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> leftLanes;
    if(laneSection->m_left)
    {
        for(auto eachLane : laneSection->m_left->m_lanes)
        {
            leftLanes.push_back(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
        }

        // 左侧车道
        for (int i = laneSection->m_left->m_lanes.size() - 1; i >= 0; --i)
        {
            qvecQvecLeftLanesPoint[i] += getCurrentLanePoint(geometry, pointfHdg, i, dLaneSectionEnd, dRelatLaneSectionS, dRelatRoadS, dRoadLength, leftLanes, qvecRelatLaneSectionSAndPointFHdg, laneRoadmarkPoint, true);
        }
    }

    m_dCurLengthToReferenc = 0.0;
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> rightLanes;
    if(laneSection->m_right)
    {
        for(auto eachLane : laneSection->m_right->m_lanes)
        {
            rightLanes.push_back(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
        }

        // 右侧车道
        for (int i = 0; i < laneSection->m_right->m_lanes.size(); ++i)
        {
            qvecQvecRightLanesPoint[i] += getCurrentLanePoint(geometry, pointfHdg, i, dLaneSectionEnd, dRelatLaneSectionS, dRelatRoadS, dRoadLength, rightLanes, qvecRelatLaneSectionSAndPointFHdg, laneRoadmarkPoint, false);
        }
    }

    qvecRelatLaneSectionSAndPointFHdg.clear();
}

void MapInfo::getGeometryIndex(const std::string& roadId, const std::vector<std::shared_ptr<t_road_planView_geometry>> &vecGeometry, int &iStartIndex, int &iEndIndex, double dLaneStart, double dLaneEnd)
{
    assert(dLaneStart <= dLaneEnd);
    std::shared_ptr<t_road_planView_geometry> eachGeometry;

    for (iStartIndex = 0; iStartIndex < vecGeometry.size(); ++iStartIndex)
    {
        eachGeometry = vecGeometry[iStartIndex];
        if(eachGeometry->s._val > dLaneStart)
        {
            break;
        }
    }

    for (iEndIndex = 0; iEndIndex < vecGeometry.size(); ++iEndIndex)
    {
        eachGeometry = vecGeometry[iEndIndex];
        if(eachGeometry->s._val >= dLaneEnd)
        {
            break;
        }
    }

    iStartIndex -= 1;
    iEndIndex -= 1;
}

void MapInfo::setLaneOffsetOpposite(std::vector<std::shared_ptr<t_road>> &vecRoad)
{
    for(auto &eachRoad : vecRoad)
    {
        for(auto &eachLaneoffset : eachRoad->m_lanes->m_laneOffsets)
        {
            eachLaneoffset->a *= -1;
            eachLaneoffset->b *= -1;
            eachLaneoffset->c *= -1;
            eachLaneoffset->d *= -1;
        }
    }
}

void MapInfo::setSGeometryOpposite(std::vector<std::shared_ptr<t_road>> &vecRoad)
{
    for(auto eachRoad : vecRoad)
    {
        for(auto &eachGeometry : eachRoad->m_planView->m_geometrys)
        {
            eachGeometry->hdg = -eachGeometry->hdg + 0.0;
            eachGeometry->y   = -eachGeometry->y + 0.0;
            if(nullptr != eachGeometry->m_t_road_planView_geometry->m_line)
            {
            }
            else if(nullptr != eachGeometry->m_t_road_planView_geometry->m_arc)
            {
                eachGeometry->m_t_road_planView_geometry->m_arc->curvature = -eachGeometry->m_t_road_planView_geometry->m_arc->curvature + 0.0;
            }
            else if(nullptr != eachGeometry->m_t_road_planView_geometry->m_spiral)
            {
                eachGeometry->m_t_road_planView_geometry->m_spiral->curvStart = -eachGeometry->m_t_road_planView_geometry->m_spiral->curvStart + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_spiral->curvEnd = -eachGeometry->m_t_road_planView_geometry->m_spiral->curvEnd + 0.0;
            }
            else if(nullptr != eachGeometry->m_t_road_planView_geometry->m_poly3)
            {
                eachGeometry->m_t_road_planView_geometry->m_poly3->a = -eachGeometry->m_t_road_planView_geometry->m_poly3->a + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_poly3->b = -eachGeometry->m_t_road_planView_geometry->m_poly3->b + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_poly3->c = -eachGeometry->m_t_road_planView_geometry->m_poly3->c + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_poly3->d = -eachGeometry->m_t_road_planView_geometry->m_poly3->d + 0.0;
            }
            else if(nullptr != eachGeometry->m_t_road_planView_geometry->m_paramPoly3)
            {
                eachGeometry->m_t_road_planView_geometry->m_paramPoly3->aV = -eachGeometry->m_t_road_planView_geometry->m_paramPoly3->aV + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_paramPoly3->bV = -eachGeometry->m_t_road_planView_geometry->m_paramPoly3->bV + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_paramPoly3->cV = -eachGeometry->m_t_road_planView_geometry->m_paramPoly3->cV + 0.0;
                eachGeometry->m_t_road_planView_geometry->m_paramPoly3->dV = -eachGeometry->m_t_road_planView_geometry->m_paramPoly3->dV + 0.0;
            }
            else
            {
                // add later
            }
        }
    }

}
