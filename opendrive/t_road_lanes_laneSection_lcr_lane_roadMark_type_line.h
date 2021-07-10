//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_TYPE_LINE_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_TYPE_LINE_H


#include "xodr_types.h"

class t_road_lanes_laneSection_lcr_lane_roadMark_type_line {
public:
    t_road_lanes_laneSection_lcr_lane_roadMark_type_line();
    virtual ~t_road_lanes_laneSection_lcr_lane_roadMark_type_line();

public:
    t_grZero length;
    t_grEqZero space;
    double tOffset;
    t_grEqZero sOffset;
    e_roadMarkRule rule;
    t_grZero width;
    e_roadMarkColor color;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_TYPE_LINE_H
