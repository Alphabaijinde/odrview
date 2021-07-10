//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_LANE_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_LANE_H


#include "t_road_lanes_laneSection_lr_lane.h"

class t_road_lanes_laneSection_center_lane : public t_road_lanes_laneSection_lr_lane {
public:
    t_road_lanes_laneSection_center_lane();
    virtual ~t_road_lanes_laneSection_center_lane();

public:
    int id;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_LANE_H
