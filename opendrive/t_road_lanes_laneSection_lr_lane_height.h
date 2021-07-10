//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_HEIGHT_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_HEIGHT_H


#include "xodr_types.h"

class t_road_lanes_laneSection_lr_lane_height {
public:
    t_road_lanes_laneSection_lr_lane_height();
    virtual ~t_road_lanes_laneSection_lr_lane_height();

public:
    t_grEqZero sOffset;
    double inner;
    double outer;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_HEIGHT_H
