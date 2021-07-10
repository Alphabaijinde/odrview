//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_SWAY_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_SWAY_H


#include "xodr_types.h"

class t_road_lanes_laneSection_lcr_lane_roadMark_sway {
public:
    t_road_lanes_laneSection_lcr_lane_roadMark_sway();
    virtual ~t_road_lanes_laneSection_lcr_lane_roadMark_sway();

public:
    t_grEqZero ds;
    double a;
    double b;
    double c;
    double d;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_SWAY_H
