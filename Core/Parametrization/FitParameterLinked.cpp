// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/FitParameterLinked.cpp
//! @brief     Implements class FitParameterLinked.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterLinked.h"
#include <stdexcept>
#include "ParameterPool.h"
#include "RealParameter.h"

FitParameterLinked::FitParameterLinked()
{
}

FitParameterLinked::FitParameterLinked(
    const std::string& name, double value, double step, const AttLimits& attlim, double error)
    : FitParameter(name, value, step, attlim, error)
{
}

FitParameterLinked::~FitParameterLinked()
{
    for (auto* par: m_pool_parameters)
        delete par;
}

//! Sets given value for all bound parameters
void FitParameterLinked::setValue(double value) {
    FitParameter::setValue(value);
    for(auto* par: m_pool_parameters)
        par->setValue(value);
}

//! Adds real parameter to the collection
void FitParameterLinked::addParameter(RealParameter* par)
{
    if( par->isNull() )
        throw std::runtime_error(
            "FitMultiParameter::addParameter() -> Attempt to add null parameter");
    m_pool_parameters.push_back(par->clone());
}

//! Adds parameters from pool which match given wildcard
void FitParameterLinked::addMatchedParametersFromPool(
    const ParameterPool* pool, const std::string& wildcard)
{
    std::string wildcard_to_use = getName();
    if( !wildcard.empty())
        wildcard_to_use = wildcard;
    for (auto* par: pool->getMatchedParameters(wildcard_to_use))
        m_pool_parameters.push_back(par->clone());
    if( m_pool_parameters.empty() )
        throw std::runtime_error(
            "FitMultiParameter::addMatchedParametersFromPool() -> Error! "
            "Failed to add anything from pool using wildcard '"+wildcard_to_use+"'");
}

void FitParameterLinked::print(std::ostream& ostr) const
{
    FitParameter::print(ostr);
    ostr << "FitParameterLinked '" << getName() << "'" << " value:" << m_value
         << " collsize:" << m_pool_parameters.size();
//    if(m_parametercoll.size() ) {
//        ostr << " addresses: ";
//        for(auto it=m_parametercoll.begin(); it!=m_parametercoll.end(); it++) {
//            parameter_t par = (*it);
//            ostr << par << " ";
//        }
//    }
}