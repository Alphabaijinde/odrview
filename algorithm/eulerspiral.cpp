#include "eulerspiral.h"

#include <complex>
#include <float.h>
#include <math.h>

#include "spiral.h"

EulerSpiral::EulerSpiral(double gamma)
{
    m_dGamma = gamma;
}

EulerSpiral EulerSpiral::createFromLengthAndCurvature(double length, double curvStart, double curvEnd)
{
    if (fabs(length) < DBL_EPSILON)
    {
        return EulerSpiral(0);
    }
    else
    {
        return EulerSpiral(1 * (curvEnd - curvStart) / length);
    }
}

PointFHdg EulerSpiral::calc(double s, double x0, double y0, double kappa0, double theta0)
{
    std::complex<double> j1(0, 1);
    auto C0 = x0 + j1 * y0;

    std::complex<double> Cs;
    if(fabs(m_dGamma) < DBL_EPSILON && fabs(kappa0) < DBL_EPSILON)
    {
        // Straight line
        Cs = C0 + exp(j1 * theta0 * s);
    }
    else if(fabs(m_dGamma) < DBL_EPSILON && fabs(kappa0) >= DBL_EPSILON)
    {
        // Arc
         Cs = C0 + exp(j1 * theta0) / kappa0 *
             (
                sin(kappa0 * s) + j1 * (1 - cos(kappa0 * s))
             );
    }
    else
    {
        // Fresnel integrals
        Spiral spiral;

        double dSa = 0, dCa = 0;
        spiral.fresnel((kappa0 + m_dGamma * s) / sqrt(M_PI * fabs(m_dGamma)), &dSa, &dCa);


        double dSb = 0, dCb = 0;
        spiral.fresnel(kappa0 / sqrt(M_PI * fabs(m_dGamma)), &dSb, &dCb);

        // Euler Spiral
        auto Cs1 = sqrt(M_PI / fabs(m_dGamma)) * exp(j1 * (theta0 - pow(kappa0, 2) / 2 / m_dGamma));

        auto Cs2 = copysign(1.0, m_dGamma) * (dCa - dCb) + j1 * dSa - j1 * dSb;
        Cs = C0 + Cs1 * Cs2;
    }

    PointFHdg pointfHdg;
    pointfHdg.qPointf = QPointF(Cs.real(), Cs.imag());
    pointfHdg.dHdg = m_dGamma * pow(s, 2) / 2 + kappa0 * s + theta0;

    return pointfHdg;
}
