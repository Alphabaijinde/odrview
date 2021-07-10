//
// Created by baijinde on 7/1/21.
//

#ifndef ODRVIEWER_T_HEADER_H
#define ODRVIEWER_T_HEADER_H

#include <string>
#include <memory>
#include "t_header_GeoReference.h"
#include "t_header_Offset.h"

class t_header {

public:
    t_header();
//    t_header(pugi::xml_node node);

    virtual ~t_header();

public:
    const int m_revMajor = 1; // Mandatory
    int m_revMinor;           // Mandatory
    std::string m_name;         // optional
    std::string m_version;      // optional
    std::string m_date;         // optional
    double m_north;             // optional
    double m_south;             // optional
    double m_east;              // optional
    double m_west;              // optional
    std::string m_vendor;       // optional

    std::shared_ptr<t_header_GeoReference> m_geoReference;
    std::shared_ptr<t_header_Offset> m_offset;
};


#endif //ODRVIEWER_T_HEADER_H
