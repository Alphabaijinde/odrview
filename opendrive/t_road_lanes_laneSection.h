//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_H


#include "xodr_types.h"
#include "t_road_lanes_laneSection_left.h"
#include "t_road_lanes_laneSection_center.h"
#include "t_road_lanes_laneSection_right.h"

class t_road_lanes_laneSection {
public:
    t_road_lanes_laneSection();
    virtual ~t_road_lanes_laneSection();

public:
    t_grEqZero s;
    t_bool singleSide;

    std::shared_ptr<t_road_lanes_laneSection_left> m_left;
    std::shared_ptr<t_road_lanes_laneSection_center> m_center;
    std::shared_ptr<t_road_lanes_laneSection_right> m_right;

    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_H
