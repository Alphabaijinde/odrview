//
// Created by baijinde on 7/5/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_ACCESS_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_ACCESS_H


#include "xodr_types.h"

class t_road_lanes_laneSection_lr_lane_access {
public:
    t_road_lanes_laneSection_lr_lane_access();
    virtual ~t_road_lanes_laneSection_lr_lane_access();

public:
    t_grEqZero sOffset;
    e_road_lanes_laneSection_lr_lane_access_rule rule;
    e_accessRestrictionType restriction;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_ACCESS_H
