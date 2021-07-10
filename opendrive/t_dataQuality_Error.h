//
// Created by baijinde on 7/4/21.
//

#ifndef ODRVIEWER_T_DATAQUALITY_ERROR_H
#define ODRVIEWER_T_DATAQUALITY_ERROR_H


class t_dataQuality_Error {
public:
    t_dataQuality_Error();
    virtual ~t_dataQuality_Error();

public:
    double xyAbsolute;
    double zAbsolute;
    double xyRelative;
    double zRelative;
};


#endif //ODRVIEWER_T_DATAQUALITY_ERROR_H
