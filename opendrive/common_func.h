//
// Created by baijinde on 7/1/21.
//

#ifndef ODRVIEWER_COMMON_H
#define ODRVIEWER_COMMON_H

template<typename T, int Tmin, int Tmax>
struct t_typevar
{
    T _val= static_cast<T>(Tmin);
    bool operator=(T value)
    {
        if (value <= Tmax && value >=Tmin)
        {
            _val = value;
            return true;
        }
        return false;
    }
    operator bool() const
    {
        if (_val <= Tmax && _val >=Tmin) return true;
        return false;
    }
    const T value() { return _val; }
};

#endif //ODRVIEWER_COMMON_H
