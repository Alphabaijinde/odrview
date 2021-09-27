#ifndef SPIRAL_H
#define SPIRAL_H

class Spiral
{
public:
    explicit Spiral();
    ~Spiral();

    void calculateSpiral(double s, double cDot, double *x, double *y, double *t);
    void fresnel(double xxa, double *ssa, double *cca);

private:
    double polevl(double x, double* coef, int n);
    double p1evl(double x, double* coef, int n);
};

#endif // SPIRAL_H
