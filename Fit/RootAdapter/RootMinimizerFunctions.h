// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootMinimizerFunctions.h
//! @brief     Defines classes RootObjectiveFunction and RootGradientFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROOTMINIMIZERFUNCTIONS_H
#define ROOTMINIMIZERFUNCTIONS_H

#include "KernelTypes.h"

#ifdef _WIN32
#include "Math/Functor.h"
#include "Math/FitMethodFunction.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/Functor.h"
#include "Math/FitMethodFunction.h"
#pragma GCC diagnostic pop
#endif

//! The chi2 function for use in minimizers.
//! @ingroup fitting_internal

class RootObjectiveFunction : public ROOT::Math::Functor
{
 public:
    RootObjectiveFunction(root_objective_t fcn, int ndims )
        : ROOT::Math::Functor(fcn, ndims) {}
};

//! Minimizer function with access to single data element residuals,
//! required by Fumili, Fumili2 and GSLMultiMin minimizers.
//! @ingroup fitting_internal

class RootGradientFunction : public ROOT::Math::FitMethodFunction
{
 public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t Type_t;

    RootGradientFunction(root_gradient_t fun_gradient, size_t npars, size_t ndatasize)
        : ROOT::Math::FitMethodFunction((int)npars, (int)ndatasize)
        , m_fun_gradient(fun_gradient) { }

    Type_t Type() const { return ROOT::Math::FitMethodFunction::kLeastSquare; }

    ROOT::Math::IMultiGenFunction* Clone() const {
        return new RootGradientFunction(m_fun_gradient, NDim(), NPoints()); }

    //! evaluation of single data element residual
    double DataElement(const double* pars, unsigned int i_data, double* gradient = 0) const {
        return m_fun_gradient(pars, i_data, gradient);
    }

 private:
    //! evaluation of chi2
    double DoEval(const double* pars) const {
        double chi2 = 0.0;
        for(size_t i_data=0; i_data<NPoints(); ++i_data) {
            double  res = DataElement(pars, (unsigned)i_data);
            chi2 += res*res;
        }
        return chi2/double(NPoints());
    }

    root_gradient_t m_fun_gradient;
};

#endif // ROOTMINIMIZERFUNCTIONS_H
