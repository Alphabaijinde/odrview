//
// Created by baijinde on 21-9-23.
//

#include "ComputeParameter.h"


ComputeParameter::ComputeParameter()
{}

ComputeParameter::~ComputeParameter()
{}

// (u, v)转(x, y)
const QPointF ComputeParameter::UVToxy(const QPointF &start, const double &dhdg, const double &u, const double &v)
{
    double distance = sqrt(pow(u, 2)+ pow(v, 2));
    return QPointF(start.x() + distance*cos(dhdg + atan2(v, u)), start.y() + distance*sin(dhdg + atan2(v, u)));
}

std::vector<QPointF> ComputeParameter::getParamPoly3DataPoint(t_road_planView_geometry geometry)
{
    if(nullptr != geometry.m_t_road_planView_geometry->m_paramPoly3.get())
    {
        return std::vector<QPointF>();
    }

    if(e_paramPoly3_pRange::ARCLENGTH == geometry.m_t_road_planView_geometry->m_paramPoly3->pRange)
    {
        geometry.m_t_road_planView_geometry->m_paramPoly3->bU    *= geometry.length._val;
        geometry.m_t_road_planView_geometry->m_paramPoly3->bV    *= geometry.length._val;
        geometry.m_t_road_planView_geometry->m_paramPoly3->cU    *= pow(geometry.length._val, 2);
        geometry.m_t_road_planView_geometry->m_paramPoly3->cV    *= pow(geometry.length._val, 2);
        geometry.m_t_road_planView_geometry->m_paramPoly3->dU    *= pow(geometry.length._val, 3);
        geometry.m_t_road_planView_geometry->m_paramPoly3->dV    *= pow(geometry.length._val, 3);
    }

    // 根据系数求（u, v）
    double u1 = geometry.m_t_road_planView_geometry->m_paramPoly3->bU/3;
    double u2 = (geometry.m_t_road_planView_geometry->m_paramPoly3->cU + 6*u1)/3;
    double u3 = geometry.m_t_road_planView_geometry->m_paramPoly3->dU - 3*u1 + 3*u2;
    double v1 = geometry.m_t_road_planView_geometry->m_paramPoly3->bV/3;
    double v2 = (geometry.m_t_road_planView_geometry->m_paramPoly3->cV + 6*v1)/3;
    double v3 = geometry.m_t_road_planView_geometry->m_paramPoly3->dV - 3*v1 + 3*v2;

    // 根据（u, v）求（x，y）
    QPointF start(geometry.x, geometry.y);
    QPointF lControllPoint = UVToxy(start, geometry.hdg, u1, v1);
    QPointF RControllPoint = UVToxy(start, geometry.hdg, u2, v2);
    QPointF end = UVToxy(start, geometry.hdg, u3, v3);

    return {start, lControllPoint, RControllPoint, end};
}
