//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_DATAQUALITY_H
#define ODRVIEWER_T_DATAQUALITY_H


#include <memory>
#include "t_dataQuality_Error.h"
#include "t_dataQuality_RawData.h"

class t_dataQuality {
public:
    t_dataQuality();
    virtual ~t_dataQuality();

public:
    std::shared_ptr<t_dataQuality_Error> m_error;
    std::shared_ptr<t_dataQuality_RawData> m_rawData;
};


#endif //ODRVIEWER_T_DATAQUALITY_H
