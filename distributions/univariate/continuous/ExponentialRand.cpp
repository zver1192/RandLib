#include "ExponentialRand.h"
#include "UniformRand.h"
#include "../BasicRandGenerator.h"

double ExponentialRand::stairWidth[257] = {0};
double ExponentialRand::stairHeight[256] = {0};
bool ExponentialRand::dummy = ExponentialRand::SetupTables();

ExponentialRand::ExponentialRand(double rate) : GammaRand()
{
    SetRate(rate);
}

std::string ExponentialRand::Name() const
{
    return "Exponential(" + toStringWithPrecision(GetRate()) + ")";
}

bool ExponentialRand::SetupTables()
{
    /// Set up ziggurat tables
    static constexpr long double A = 3.9496598225815571993e-3l; /// area under rectangle

    /// coordinates of the implicit rectangle in base layer
    stairHeight[0] = 0.00045413435384149675; /// std::exp(-x1);
    stairWidth[0] = 8.697117470131049720307; /// A / stairHeight[0];
    /// implicit value for the top layer
    stairWidth[256] = 0;

    stairWidth[1] = x1;
    stairHeight[1] = 0.0009672692823271745203;

    for (size_t i = 2; i < 256; ++i)
    {
        /// such y_i that f(x_{i+1}) = y_i
        stairWidth[i] = -std::log(stairHeight[i - 1]);
        stairHeight[i] = stairHeight[i - 1] + A / stairWidth[i];
    }
    return true;
}

void ExponentialRand::SetRate(double rate)
{
    SetParameters(1, rate);
}

double ExponentialRand::f(double x) const
{
    return (x >= 0) ? beta * std::exp(-beta * x) : 0;
}

double ExponentialRand::F(double x) const
{
    return (x > 0) ? 1 - std::exp(-beta * x) : 0;
}

double ExponentialRand::Variate() const
{
    return theta * StandardVariate();
}

double ExponentialRand::Variate(double rate)
{
    return StandardVariate() / rate;
}

double ExponentialRand::StandardVariate()
{
    /// Ziggurat algorithm
    int iter = 0;
    do {
        int stairId = RandGenerator::variate() & 255;
        double x = UniformRand::StandardVariate() * stairWidth[stairId]; /// Get horizontal coordinate

        if (x < stairWidth[stairId + 1]) /// if we are under the upper stair - accept
            return x;

        if (stairId == 0) /// if we catch the tail
            return x1 + StandardVariate();

        if (UniformRand::Variate(stairHeight[stairId - 1], stairHeight[stairId]) < std::exp(-x)) /// if we are under the curve - accept
            return x;

        /// rejection - go back

    } while (++iter <= MAX_ITER_REJECTION);
    return NAN; /// fail due to some error
}

std::complex<double> ExponentialRand::CF(double t) const
{
    return 1.0 / std::complex<double>(1.0, -theta * t);
}

double ExponentialRand::quantileImpl(double p) const
{
    return -theta * std::log1p(-p);
}

double ExponentialRand::quantileImpl1m(double p) const
{
    return -theta * std::log(p);
}

double ExponentialRand::Median() const
{
    return theta * M_LN2;
}

double ExponentialRand::Entropy() const
{
    return 1 - std::log(beta);
}

double ExponentialRand::Moment(int n) const
{
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    return std::exp(std::lgamma(n + 1) - n * std::log(beta));
}

bool ExponentialRand::FitMM(const std::vector<double> &sample)
{
    return FitScaleMLE(sample);
}

bool ExponentialRand::FitMLE(const std::vector<double> &sample)
{
    return FitScaleMLE(sample);
}

bool ExponentialRand::FitUMVU(const std::vector<double> &sample)
{   
    int n = sample.size();
    if (n <= 1 || !checkValidity(sample))
        return false;
    double mean = sampleMean(sample);
    SetRate((n - 1) * mean / n);
    return true;
}
