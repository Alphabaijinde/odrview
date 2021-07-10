//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LEFT_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LEFT_H


#include <vector>
#include "t_road_lanes_laneSection_left_lane.h"
#include "g_additionalData.h"

class t_road_lanes_laneSection_left {
public:
    t_road_lanes_laneSection_left();
    virtual ~t_road_lanes_laneSection_left();

public:
    std::vector< std::shared_ptr<t_road_lanes_laneSection_left_lane> > m_lanes;
    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LEFT_H
