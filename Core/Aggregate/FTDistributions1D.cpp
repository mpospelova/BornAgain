// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FTDistributions1D.cpp
//! @brief     Implements interface class IFTDistribution2D and children thereof.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FTDistributions1D.h"
#include "BornAgainNamespace.h"
#include "IntegratorReal.h"
#include "MathFunctions.h"
#include "ParameterPool.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include <limits>

void IFTDistribution1D::init_parameters()
{
    registerParameter(BornAgain::Omega, &m_omega);
}


FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
: IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DCauchyType);
    init_parameters();
}

FTDistribution1DCauchy* FTDistribution1DCauchy::clone() const
{
    return new FTDistribution1DCauchy(m_omega);
}

double FTDistribution1DCauchy::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return 1.0/(1.0 + sum_sq);
}

FTDistribution1DGauss::FTDistribution1DGauss(double omega)
: IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DGaussType);
    init_parameters();
}

FTDistribution1DGauss* FTDistribution1DGauss::clone() const
{
    return new FTDistribution1DGauss(m_omega);
}

double FTDistribution1DGauss::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return std::exp(-sum_sq/2.0);
}

FTDistribution1DGate::FTDistribution1DGate(double omega)
    : IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DGateType);
    init_parameters();
}

FTDistribution1DGate* FTDistribution1DGate::clone() const
{
    return new FTDistribution1DGate(m_omega);
}

double FTDistribution1DGate::evaluate(double q) const
{
    return MathFunctions::sinc(q*m_omega);
}

FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
    : IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DTriangleType);
    init_parameters();
}

FTDistribution1DTriangle* FTDistribution1DTriangle::clone() const
{
    return new FTDistribution1DTriangle(m_omega);
}

double FTDistribution1DTriangle::evaluate(double q) const
{
    double sincqw2 = MathFunctions::sinc(q*m_omega/2.0);
    return sincqw2*sincqw2;
}

FTDistribution1DCosine::FTDistribution1DCosine(double omega)
    : IFTDistribution1D(omega)
{
    setName(BornAgain::FTDistribution1DCosineType);
    init_parameters();
}

FTDistribution1DCosine* FTDistribution1DCosine::clone() const
{
    return new FTDistribution1DCosine(m_omega);
}

double FTDistribution1DCosine::evaluate(double q) const
{
    double qw = std::abs(q*m_omega);
    if (std::abs(qw/M_PI-1.0) < std::numeric_limits<double>::epsilon())
        return 0.5;
    return MathFunctions::sinc(qw)/(1.0-qw*qw/M_PI/M_PI);
}

FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
    : IFTDistribution1D(omega)
    , m_eta(eta)
{
    setName(BornAgain::FTDistribution1DVoigtType);
    init_parameters();
    registerParameter(BornAgain::Eta, &m_eta);
}

FTDistribution1DVoigt* FTDistribution1DVoigt::clone() const
{
    return new FTDistribution1DVoigt(m_omega, m_eta);
}

double FTDistribution1DVoigt::evaluate(double q) const
{
    double sum_sq = q*q*m_omega*m_omega;
    return m_eta*std::exp(-sum_sq/2.0) + (1.0 - m_eta)*1.0/(1.0 + sum_sq);
}
