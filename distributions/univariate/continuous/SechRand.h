#ifndef SECHRAND_H
#define SECHRAND_H

#include "ContinuousDistribution.h"

/**
 * @brief The SechRand class
 */
class RANDLIBSHARED_EXPORT SechRand : public ContinuousDistribution
{
public:
    SechRand();

    std::string Name() const override;
    SUPPORT_TYPE SupportType() const override { return INFINITE_T; }
    double MinValue() const override { return -INFINITY; }
    double MaxValue() const override { return INFINITY; }
    double f(double x) const override;
    double F(double x) const override;
    double Variate() const override;

    double Mean() const override;
    double Variance() const override;
    double Median() const override;
    double Mode() const override;
    double Skewness() const override;
    double Kurtosis() const override;
    std::complex<double> CF(double t) const override;

private:
    double quantileImpl(double p) const;
    double quantileImpl1m(double p) const;

public:
    double Entropy() const;
};

#endif // SECHRAND_H
