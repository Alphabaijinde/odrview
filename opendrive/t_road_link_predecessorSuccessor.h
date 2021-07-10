//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LINK_PREDECESSORSUCCESSOR_H
#define ODRVIEWER_T_ROAD_LINK_PREDECESSORSUCCESSOR_H


#include <string>
#include "xodr_types.h"

class t_road_link_predecessorSuccessor {
public:
    t_road_link_predecessorSuccessor();
    virtual ~t_road_link_predecessorSuccessor();

public:
    std::string elementId;

private:
    e_road_link_elementType elementType;
    e_contactPoint contactPoint;
    t_grEqZero elementS;
    e_elementDir elementDir;
};


#endif //ODRVIEWER_T_ROAD_LINK_PREDECESSORSUCCESSOR_H
