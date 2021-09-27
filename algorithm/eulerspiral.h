#ifndef EULERSPIRAL_H
#define EULERSPIRAL_H

#include "../util/ComputeParameter.h"

class EulerSpiral
{
public:
    static EulerSpiral createFromLengthAndCurvature(double length, double curvStart, double curvEnd);

    PointFHdg calc(double s, double x0 = 0, double y0 = 0, double kappa0 = 0, double theta0 = 0);

private:
    EulerSpiral(double gamma);

    double m_dGamma;
};

#endif // EULERSPIRAL_H
