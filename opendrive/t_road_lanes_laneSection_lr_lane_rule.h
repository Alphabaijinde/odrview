//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_RULE_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_RULE_H


#include "xodr_types.h"
#include <string>

class t_road_lanes_laneSection_lr_lane_rule {
public:
    t_road_lanes_laneSection_lr_lane_rule();
    virtual ~t_road_lanes_laneSection_lr_lane_rule();

public:
    t_grEqZero sOffset;
    std::string value;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_RULE_H
