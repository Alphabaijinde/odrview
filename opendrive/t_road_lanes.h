//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_H
#define ODRVIEWER_T_ROAD_LANES_H


#include <memory>
#include <vector>
#include "t_road_lanes_laneOffset.h"
#include "t_road_lanes_laneSection.h"

class t_road_lanes {
public:
    t_road_lanes();
    virtual ~t_road_lanes();

public:
    std::vector< std::shared_ptr<t_road_lanes_laneOffset> > m_laneOffsets;
    std::vector< std::shared_ptr<t_road_lanes_laneSection> > m_laneSections;
    std::shared_ptr<g_additionalData> m_g_additionalData;
};


#endif //ODRVIEWER_T_ROAD_LANES_H
