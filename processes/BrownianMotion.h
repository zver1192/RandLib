#ifndef BROWNIANMOTION_H
#define BROWNIANMOTION_H

#include "StableProcess.h"
#include "../distributions/univariate/continuous/NormalRand.h"

/**
 * @brief The BrownianMotion class
 * dX(t) = μdt + σdB(t),
 * where B(t) - B(s) ~ Normal(0, t - s) for t > s, μ is drift and σ is volatility.
 */
class RANDLIBSHARED_EXPORT BrownianMotion : public StableProcess
{
public:
    explicit BrownianMotion(double deltaT = 1.0);
    BrownianMotion(double drift, double volatility, double deltaT = 1.0);

private:
    void nextImpl() override;
    double QuantileImpl(double t, double p) const override;
};


#endif // BROWNIANMOTION_H
