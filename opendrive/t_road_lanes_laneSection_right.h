//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_RIGHT_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_RIGHT_H


#include "g_additionalData.h"
#include "t_road_lanes_laneSection_right_lane.h"

class t_road_lanes_laneSection_right {
public:
    t_road_lanes_laneSection_right();
    virtual ~t_road_lanes_laneSection_right();

public:
    std::vector< std::shared_ptr<t_road_lanes_laneSection_right_lane> > m_lanes;
    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_RIGHT_H
