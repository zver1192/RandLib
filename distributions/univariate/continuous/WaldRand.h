#ifndef WALDRAND_H
#define WALDRAND_H

#include "ContinuousDistribution.h"

/**
 * @brief The WaldRand class
 * Wald (Inverse Gaussian) distribution
 * X ~ IG(μ, λ)
 */
class RANDLIBSHARED_EXPORT WaldRand : public ContinuousDistribution
{
    double mu, lambda;

    double pdfCoef; /// √(λ / (2π))
    double cdfCoef; /// \exp(2λ / μ)
public:
    WaldRand(double mean = 1, double shape = 1);

    std::string name() const override;
    SUPPORT_TYPE supportType() const override { return RIGHTSEMIFINITE_T; }
    double MinValue() const override { return 0; }
    double MaxValue() const override { return INFINITY; }

    void setParameters(double mean, double shape);
    inline double getMean() const { return mu; }
    inline double getShape() const { return lambda; }

    double f(double x) const override;
    double F(double x) const override;
    double variate() const override;

    double Mean() const override { return mu; }
    double Variance() const override { return mu * mu * mu / lambda; }

    std::complex<double> CF(double t) const override;
    
    double Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;
};


#endif // WALDRAND_H
