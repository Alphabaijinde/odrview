//
// Created by baijinde on 7/1/21.
//

#ifndef ODRVIEWER_T_ROAD_H
#define ODRVIEWER_T_ROAD_H

#include <string>

#include "xodr_types.h"
#include "t_road_link.h"
#include "t_road_lanes.h"

class t_road {
public:
    t_road();
    virtual ~t_road();

public:
    std::string m_name;    // optional
    t_grZero length;
    std::string m_id;
    std::string m_junction;
    e_trafficRule rule;

    std::shared_ptr<t_road_link> m_link;
    std::shared_ptr<t_road_lanes> m_lanes;
};


#endif //ODRVIEWER_T_ROAD_H
