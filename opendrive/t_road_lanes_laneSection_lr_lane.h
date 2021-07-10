//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_H
#define ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_H


#include "xodr_types.h"
#include "g_additionalData.h"
#include "t_road_lanes_laneSection_lcr_lane_link.h"
#include "t_road_lanes_laneSection_lr_lane_speed.h"
#include "t_road_lanes_laneSection_lr_lane_material.h"
#include "t_road_lanes_laneSection_lr_lane_access.h"
#include "t_road_lanes_laneSection_lr_lane_rule.h"
#include "t_road_lanes_laneSection_lcr_lane_roadMark.h"
#include "t_road_lanes_laneSection_lr_lane_height.h"

class t_road_lanes_laneSection_lr_lane {
public:
    t_road_lanes_laneSection_lr_lane();
    virtual ~t_road_lanes_laneSection_lr_lane();

public:
    e_laneType type;
    t_bool level;

    std::shared_ptr<t_road_lanes_laneSection_lcr_lane_link> m_link;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lr_lane_speed> > m_speeds;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lr_lane_material> > m_materials;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lr_lane_access> > m_accesss;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lr_lane_rule> > m_rules;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lcr_lane_roadMark> > m_roadMarks;
    std::vector< std::shared_ptr<t_road_lanes_laneSection_lr_lane_height> > m_heights;

    std::shared_ptr<g_additionalData> m_g_additionalData;

};


#endif //ODRVIEWER_T_ROAD_LANES_LANESECTION_LR_LANE_H
