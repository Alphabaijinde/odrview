//
// Created by baijinde on 7/5/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_LINK_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_LINK_H


#include "g_additionalData.h"
#include "t_road_lanes_laneSection_lcr_lane_link_predecessorSuccessor.h"

class t_road_lanes_laneSection_lcr_lane_link {
public:
    t_road_lanes_laneSection_lcr_lane_link();
    virtual ~t_road_lanes_laneSection_lcr_lane_link();

public:
    std::shared_ptr<t_road_lanes_laneSection_lcr_lane_link_predecessorSuccessor> m_predecessor;
    std::shared_ptr<t_road_lanes_laneSection_lcr_lane_link_predecessorSuccessor> m_successor;

    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_LINK_H
