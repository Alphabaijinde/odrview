//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_H


#include "g_additionalData.h"
#include "t_road_lanes_laneSection_center_lane.h"

class t_road_lanes_laneSection_center {
public:
    t_road_lanes_laneSection_center();
    virtual ~t_road_lanes_laneSection_center();

public:
    std::shared_ptr<t_road_lanes_laneSection_center_lane> m_lane;
    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_CENTER_H
