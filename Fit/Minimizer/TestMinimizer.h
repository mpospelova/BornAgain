// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/TestMinimizer.h
//! @brief     Defines class TestMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef TESTMINIMIZER_H
#define TESTMINIMIZER_H

#include "IMinimizer.h"
class FitParameterSet;

//! A trivial minimizer that calls the objective function once. Used to test the whole chain.

class BA_CORE_API_ TestMinimizer : public IMinimizer
{
 public:
    TestMinimizer() : m_min_value(0) {}
    ~TestMinimizer(){}

    std::string minimizerName() const final;
    std::string algorithmName() const final { return ""; }

    void minimize() override;

    void setParameters(const FitParameterSet& parameters) override;

    void setObjectiveFunction(objective_function_t func) override;

    std::string reportOutcome() const override;

    using IMinimizer::propagateResults;
    void propagateResults(FitParameterSet&) override;

    Fit::MinimizerResult minimize_scalar(fcn_scalar_t fcn, Fit::Parameters parameters) override;

 private:
    double m_min_value;
    std::vector<double> m_parameter_values;
    objective_function_t m_fcn;
};

#endif // TESTMINIMIZER_H
