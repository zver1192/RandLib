#ifndef POISSONRAND_H
#define POISSONRAND_H

#include "DiscreteDistribution.h"
#include "../continuous/GammaRand.h"

/**
 * @brief The PoissonRand class
 *
 * P(X = k) = λ^k * e^(-λ) / k!
 */
class RANDLIBSHARED_EXPORT PoissonRand : public DiscreteDistribution
{
    double lambda;
    double expmLambda; /// exp(-λ)
    double logLambda; /// ln(λ)
    int floorLambda; /// floor(λ)
    double FFloorLambda; /// P(X < floor(λ))
    double PFloorLambda; /// P(X = floor(λ))

public:
    explicit PoissonRand(double rate = 1.0);
    std::string name() const override;
    SUPPORT_TYPE supportType() const override { return RIGHTSEMIFINITE_T; }
    double MinValue() const override { return 0; }
    double MaxValue() const override { return INFINITY; }

    void setRate(double rate);
    inline double getRate() const { return lambda; }

    double P(int k) const override;
    double F(int k) const override;
    int variate() const override;
    static int variate(double rate);

    double Mean() const override;
    double Variance() const override;

    std::complex<double> CF(double t) const override;

    double Median() const override;
    int Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;

    bool checkValidity(const std::vector<double> &sample);

    bool fitRateMLE(const std::vector<double> &sample);
    bool fitRateBayes(const std::vector<double> &sample, GammaRand & priorDistribution);
};

#endif // POISSONRAND_H
