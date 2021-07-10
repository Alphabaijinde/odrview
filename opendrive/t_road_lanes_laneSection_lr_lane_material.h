//
// Created by baijinde on 7/5/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_MATERIAL_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_MATERIAL_H


#include <string>
#include "xodr_types.h"

class t_road_lanes_laneSection_lr_lane_material {
public:
    t_road_lanes_laneSection_lr_lane_material();
    virtual ~t_road_lanes_laneSection_lr_lane_material();

public:
    t_grEqZero sOffset;
    std::string surface;
    t_grEqZero friction;
    t_grEqZero roughness;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_MATERIAL_H
