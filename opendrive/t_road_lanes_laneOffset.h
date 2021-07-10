//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LANES_LANEOFFSET_H
#define ODRVIEWER_T_ROAD_LANES_LANEOFFSET_H


#include "xodr_types.h"

class t_road_lanes_laneOffset {
public:
    t_road_lanes_laneOffset();
    virtual ~t_road_lanes_laneOffset();

public:
    t_grEqZero s;
    double a;
    double b;
    double c;
    double d;
};


#endif //ODRVIEWER_T_ROAD_LANES_LANEOFFSET_H
