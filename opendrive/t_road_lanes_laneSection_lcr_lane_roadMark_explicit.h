//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_EXPLICIT_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_EXPLICIT_H


#include "g_additionalData.h"
#include "t_road_lanes_laneSection_lcr_lane_roadMark_explicit_line.h"

class t_road_lanes_laneSection_lcr_lane_roadMark_explicit {
public:
    t_road_lanes_laneSection_lcr_lane_roadMark_explicit();
    virtual ~t_road_lanes_laneSection_lcr_lane_roadMark_explicit();

public:
    std::vector<std::shared_ptr<t_road_lanes_laneSection_lcr_lane_roadMark_explicit_line>> m_lines;

    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_EXPLICIT_H
