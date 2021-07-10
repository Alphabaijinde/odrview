//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_ROAD_LINK_H
#define ODRVIEWER_T_ROAD_LINK_H


#include <memory>
#include "t_road_link_predecessorSuccessor.h"

class t_road_link {
public:
    t_road_link();
    virtual ~t_road_link();

public:
    std::shared_ptr<t_road_link_predecessorSuccessor> m_predecessor;
    std::shared_ptr<t_road_link_predecessorSuccessor> m_successor;

};


#endif //ODRVIEWER_T_ROAD_LINK_H
