//
// Created by baijinde on 7/10/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_H


#include "xodr_types.h"
#include "g_additionalData.h"
#include "t_road_lanes_laneSection_lcr_lane_roadMark_sway.h"
#include "t_road_lanes_laneSection_lcr_lane_roadMark_type.h"
#include "t_road_lanes_laneSection_lcr_lane_roadMark_explicit.h"
#include <string>

class t_road_lanes_laneSection_lcr_lane_roadMark {
public:
    t_road_lanes_laneSection_lcr_lane_roadMark();
    virtual ~t_road_lanes_laneSection_lcr_lane_roadMark();

public:
    t_grEqZero sOffset;
    e_roadMarkType type;
    e_roadMarkWeight weight;
    e_roadMarkColor color;
    std::string material;
    t_grEqZero width;
    e_road_lanes_laneSection_lcr_lane_roadMark_laneChange laneChange;
    double height;

    std::vector<std::shared_ptr<t_road_lanes_laneSection_lcr_lane_roadMark_sway>> m_sways;
    std::shared_ptr<t_road_lanes_laneSection_lcr_lane_roadMark_type> m_type;
    std::shared_ptr<t_road_lanes_laneSection_lcr_lane_roadMark_explicit> m_explicit;
    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LCR_LANE_ROADMARK_H
