//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_G_ADDITIONALDATA_H
#define ODRVIEWER_G_ADDITIONALDATA_H


#include <memory>
#include <vector>
#include "t_include.h"
#include "t_userData.h"
#include "t_dataQuality.h"

class g_additionalData {
public:
    g_additionalData();
    virtual ~g_additionalData();

public:
    std::vector< std::shared_ptr<t_include> > m_includes;
    std::vector< std::shared_ptr<t_userData> > m_userData;

    std::shared_ptr<t_dataQuality> m_dataQuality;
};


#endif //ODRVIEWER_G_ADDITIONALDATA_H
