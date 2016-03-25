#ifndef LAPLACERAND_H
#define LAPLACERAND_H

#include "ExponentialRand.h"

/**
 * @brief The LaplaceRand class
 */
class RANDLIBSHARED_EXPORT LaplaceRand : public ContinuousDistribution
{
    double mu, b;
    double bInv; /// 1 / b

public:
    LaplaceRand(double location = 0, double scale = 1);
    std::string name() override;

    void setLocation(double location);
    void setScale(double scale);
    inline double getLocation() const { return mu; }
    inline double getScale() const { return b; }

    double f(double x) const override;
    double F(double x) const override;
    double variate() const override;
    static double variate(double location, double scale);

    double Mean() const override;
    double Variance() const override;

    double Median() const override;
    double Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;
    
    std::complex<double> CF(double t) const override;

    /// Maximum likelihood estimation
    bool fitLocationMLE(const std::vector<double> &sample);
    bool fitScaleMLE(const std::vector<double> &sample);
    bool fitLocationAndScaleMLE(const std::vector<double> &sample);
    
    /// Method of moments
    bool fitLocationMM(const std::vector<double> &sample);
    bool fitScaleMM(const std::vector<double> &sample);
    bool fitLocationAndScaleMM(const std::vector<double> &sample);
};

#endif // LAPLACERAND_H