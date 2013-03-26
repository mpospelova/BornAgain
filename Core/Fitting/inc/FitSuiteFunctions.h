// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/inc/FitSuiteFunctions.h
//! @brief     Defines classes IFitSuiteFunction,
//!              FitSuiteChiSquaredFunction, FitSuiteGradientFunction
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#ifndef FITSUITEFUNCTIONS_H
#define FITSUITEFUNCTIONS_H

#include <vector>
#include <cstddef>
using std::size_t;

class FitSuite;

//! Fitting functions interface to be used by Minimizer.

class IFitSuiteFunction
{
 public:
    IFitSuiteFunction() : m_fit_suite(0), m_ncall(0) {}
    virtual ~IFitSuiteFunction(){}
    virtual void init(FitSuite *fit_suite) { m_fit_suite = fit_suite; }
    virtual size_t getNCalls() const { return m_ncall; }
 protected:
    FitSuite *m_fit_suite;
    size_t m_ncall;
};

//! Chi squared fitting function for minimizer

class FitSuiteChiSquaredFunction : public IFitSuiteFunction
{
 public:
    FitSuiteChiSquaredFunction(){}
    virtual ~FitSuiteChiSquaredFunction(){}
    //! evaluate method for chi2 value called directly from the minimizer
    double evaluate(const double *pars);
};

//! Gradient fitting function for minimizer

class FitSuiteGradientFunction : public IFitSuiteFunction
{
 public:
    FitSuiteGradientFunction() : m_npars(0), m_ndatasize(0), m_prev_index(-1), m_ncalls_total(0), m_ncalls_gradient(0) {}
    virtual ~FitSuiteGradientFunction(){}
    //! evaluate method for gradients and residuals called directly from the minimizer
    double evaluate(const double *pars, unsigned int index, double *gradients);
    virtual size_t getNCallsTotal() const { return m_ncalls_total; }
    virtual size_t getNCallsGradient() const { return m_ncalls_gradient; }

 private:
    void verify_arrays();
    void verify_minimizer_logic(bool parameters_have_changed, int current_index);
    void calculate_residuals(const double *pars);
    void calculate_gradients(const double *pars);
    void runSimulation(const double *pars);

    size_t m_npars;
    size_t m_ndatasize;
    int m_prev_index;
    std::vector<double > m_residuals; // [m_ndatasize]
    std::vector<std::vector<double> > m_gradients; // [m_npars][m_ndatasize]
    size_t m_ncalls_total;
    size_t m_ncalls_gradient;
};

#endif // FITSUITEFUNCTIONS_H
