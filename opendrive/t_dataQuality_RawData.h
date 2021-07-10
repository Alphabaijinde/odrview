//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_DATAQUALITY_RAWDATA_H
#define ODRVIEWER_T_DATAQUALITY_RAWDATA_H


#include <string>
#include "xodr_types.h"

class t_dataQuality_RawData {
public:
    t_dataQuality_RawData();
    virtual ~t_dataQuality_RawData();

public:
    std::string date;
    e_dataQuality_RawData_Source source;
    std::string sourceComment;
    e_dataQuality_RawData_PostProcessing postProcessing;
    std::string postProcessingComment;
};


#endif //ODRVIEWER_T_DATAQUALITY_RAWDATA_H
