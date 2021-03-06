// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ISquaredFunction.h
//! @brief     Defines classes ISquaredFunction, SquaredFunctionDefault, ...
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ISQUAREDFUNCTION_H
#define ISQUAREDFUNCTION_H

#include "WinDllMacros.h"

//! Interface providing measures for deviation between two values.
//! Used By ChiSquaredModule for chi2 calculations.
//! @ingroup fitting_internal

class BA_CORE_API_ ISquaredFunction
{
public:
    ISquaredFunction() {}
    virtual ~ISquaredFunction() {}
    virtual ISquaredFunction* clone() const =0;
    virtual double calculateSquaredDifference(
                double real_value, double simulated_value) const =0;
    virtual double calculateSquaredError(
                double real_value, double simulated_value = 0.0) const =0;

    ISquaredFunction(const ISquaredFunction& ) = delete;
    ISquaredFunction& operator=(const ISquaredFunction& ) = delete;
};


//! Squared difference between two values.
//! value = (a-b)*(a-b)/norm, where norm = max(b, 1.0), a = simulated values, b = real_values.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionDefault : public ISquaredFunction
{
public:
    SquaredFunctionDefault() {}
    ~SquaredFunctionDefault() {}
    SquaredFunctionDefault* clone() const override;
    double calculateSquaredDifference(double real_value, double simulated_value) const override;
    double calculateSquaredError(double real_value, double simulated_value = 0) const override;
};


//! Squared difference between two values.
//! value = (a-b)*(a-b)/norm, where norm = max(a, 1.0), a = simulated values, b = real_values.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionSimError : public ISquaredFunction
{
public:
    SquaredFunctionSimError() {}
    ~SquaredFunctionSimError() {}
    SquaredFunctionSimError *clone() const override;
    double calculateSquaredDifference(double real_value, double simulated_value) const override;
    double calculateSquaredError(double real_value, double simulated_value) const override;
};


//! Squared difference between two values normalized by mean squared error.
//! value = (a-b)*(a-b)/norm, where norm = sqrt(sigma1*sigma1 + sigma2*sigma2),
//! sigma1=max(a, 1.0), sigma2=max(b,1.0)
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionMeanSquaredError : public ISquaredFunction
{
public:
    SquaredFunctionMeanSquaredError() {}
    ~SquaredFunctionMeanSquaredError() {}
    SquaredFunctionMeanSquaredError* clone() const override;
    double calculateSquaredDifference(double real_value, double simulated_value) const override;
    double calculateSquaredError(double real_value, double simulated_value) const override;
};


//! Squared difference between two values normalized by systematic error.
//! value = (a-b)*(a-b)/norm, where norm = max(error, 1.0), error = b + (epsilon*b)**2.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionSystematicError : public ISquaredFunction
{
public:
    SquaredFunctionSystematicError(double epsilon = 0.08) : m_epsilon(epsilon){}
    ~SquaredFunctionSystematicError() {}
    SquaredFunctionSystematicError *clone() const override;
    double calculateSquaredDifference(double real_value, double simulated_value) const override;
    double calculateSquaredError(double real_value, double simulated_value) const override;
private:
    double m_epsilon;
};


//! Squared difference between two values with gaussian error.
//! value = (a-b)*(a-b)/norm, where norm = sigma*sigma; sigma is set by user.
//! @ingroup fitting

class BA_CORE_API_ SquaredFunctionGaussianError : public ISquaredFunction
{
public:
    SquaredFunctionGaussianError(double sigma = 0.01) : m_sigma(sigma){}
    ~SquaredFunctionGaussianError() {}
    SquaredFunctionGaussianError *clone() const override;
    double calculateSquaredDifference(double real_value, double simulated_value) const override;
    double calculateSquaredError(double real_value, double simulated_value) const override;
private:
    double m_sigma;
};

#endif // ISQUAREDFUNCTION_H
