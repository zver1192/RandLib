#include "UniformRand.h"

UniformRand::UniformRand(double minValue, double maxValue)
{
    setBoundaries(minValue, maxValue);
}

void UniformRand::setBoundaries(double minValue, double maxValue)
{
    a = minValue;
    b = maxValue;

    /// Sanity check
    if (b < a)
        swapBoundaries();
    if (b == a)
        c = INFINITY;
    else
        c = 1.0 / (b - a);
}

void UniformRand::swapBoundaries()
{
    a += b;
    b -= a;
    a += b;
    b = -b;
}

double UniformRand::value()
{
    double rv = .5 + (signed)fastKISS() * .23283064e-9; /// ~ U(0, 1)
    rv *= (b - a); /// ~ U(0, b - a)
    return rv + a; /// ~ U(a, b)
}

double UniformRand::f(double x) const
{
    return (x >= a && x <= b) ? c : 0;
}

double UniformRand::F(double x) const
{
    if (x < a)
        return 0;
    if (x > b)
        return 1;
    return c * (x - a);
}

bool UniformRand::fitToData(const QVector<double> &sample)
{
    if (sample.size() == 0)
        return false;
    double maxVar = sample.at(0), minVar = maxVar;
    for (double var : sample) {
        maxVar = std::max(var, maxVar);
        minVar = std::min(var, minVar);
    }

    setBoundaries(minVar, maxVar);
    return true;
}