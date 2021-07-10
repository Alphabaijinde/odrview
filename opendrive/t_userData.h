//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_USERDATA_H
#define ODRVIEWER_T_USERDATA_H


#include <string>

class t_userData {
public:
    t_userData();
    virtual ~t_userData();

public:
    std::string code;
    std::string value;
};


#endif //ODRVIEWER_T_USERDATA_H
