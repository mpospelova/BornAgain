// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.h
//! @brief     Defines class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef IMINIMIZER_H
#define IMINIMIZER_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include "MinimizerResult.h"
#include <string>

class FitParameterSet;
namespace Fit {class Parameters;}

//! Pure virtual interface for all kind minimizers.
//! @ingroup fitting_internal

class BA_CORE_API_ IMinimizer
{
 public:
    IMinimizer() {}
    virtual ~IMinimizer() {}

    IMinimizer(const IMinimizer &other) =delete;
    IMinimizer& operator=(const IMinimizer& other) =delete;

    //! return name of the minimizer
    virtual std::string minimizerName() const =0;

    //! return name of the minimization algorithm
    virtual std::string algorithmName() const =0;

    //! run minimization
    virtual void minimize() =0;
    virtual Fit::MinimizerResult minimize_scalar(fcn_scalar_t, Fit::Parameters);
    virtual Fit::MinimizerResult minimize_residual(fcn_residual_t, Fit::Parameters);

    //! clear resources (parameters) for consecutives minimizations
    virtual void clear() {}

    //! Sets internal minimizer parameters using external parameter list
    virtual void setParameters(const FitParameterSet& parameters) =0;

    virtual void setObjectiveFunction(objective_function_t ) {}

    virtual void setGradientFunction(gradient_function_t, int ) {}

    //! Returns minimum function value
    virtual double minValue() const;

    virtual std::string reportOutcome() const =0;

    //! Propagates results of minimization to fit parameter set
    virtual void propagateResults(FitParameterSet& parameters);
    virtual void propagateResults(Fit::Parameters& parameters);

    //! Sets option string to the minimizer
    virtual void setOptions(const std::string& options);
};

#endif // IMINIMIZER_H
