//
// Created by baijinde on 7/5/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_SPEED_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_SPEED_H


#include "xodr_types.h"

class t_road_lanes_laneSection_lr_lane_speed {
public:
    t_road_lanes_laneSection_lr_lane_speed();
    virtual ~t_road_lanes_laneSection_lr_lane_speed();

public:
    t_grEqZero sOffset;
    t_grEqZero max;
    e_unitSpeed unit;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_SPEED_H
