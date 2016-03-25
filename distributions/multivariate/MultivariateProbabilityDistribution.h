#ifndef MULTIVARIATEPROBABILITYDISTRIBUTION_H
#define MULTIVARIATEPROBABILITYDISTRIBUTION_H

#include "../ProbabilityDistribution.h"
#include "../../math/Matrix.h"

class RANDLIBSHARED_EXPORT MultivariateProbabilityDistribution : public ProbabilityDistribution< std::vector<double> >
{
public:
    MultivariateProbabilityDistribution();
    virtual ~MultivariateProbabilityDistribution() {}

    virtual double f(std::vector<double> point) const = 0;

    virtual bool Covariance(Matrix &matrix) const = 0;
};

#endif // MULTIVARIATEPROBABILITYDISTRIBUTION_H