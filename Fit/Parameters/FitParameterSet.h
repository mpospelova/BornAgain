// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameterSet.h
//! @brief     Defines class FitParameterSet.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITPARAMETERSET_H
#define FITPARAMETERSET_H

#include "WinDllMacros.h"
#include <vector>
#include <string>

class IFitParameter;

//! The set of fit parameters.
//! @ingroup fitting_internal

class BA_CORE_API_ FitParameterSet
{
 public:
    typedef std::vector<IFitParameter*> container_t;
    typedef container_t::iterator iterator;
    typedef container_t::const_iterator const_iterator;
    typedef std::vector<std::vector<double>> corr_matrix_t;

    FitParameterSet() {}
    ~FitParameterSet();

    void clear();
    size_t size() const;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void addFitParameter(IFitParameter* par);

    // Access fit parameters

    const IFitParameter* fitParameter(const std::string& name) const;
    IFitParameter* fitParameter(const std::string& name);
    const IFitParameter* operator[](const std::string& name) const;
    IFitParameter* operator[](const std::string& name);
    const IFitParameter* operator[](size_t index) const;
    IFitParameter* operator[](size_t index);

    // Fit parameter's values and errors

    std::vector<double> values() const;
    void setValues(const std::vector<double>& pars_values);
    bool valuesDifferFrom(const std::vector<double>& par_values, double tolerance = 2.0) const;
    std::vector<double> errors() const;
    void setErrors(const std::vector<double>& pars_errors);

    // Make parameters fixed and free

    size_t freeFitParameterCount() const;
    void fixAll();
    void releaseAll();
    void setFixed(const std::vector<std::string>& pars, bool is_fixed);

    corr_matrix_t correlationMatrix() const { return m_corr_matrix; }
    void setCorrelationMatrix(const corr_matrix_t& matrix);

private:
    bool isExistingName(const std::string& name) const;
    std::string suggestParameterName() const;
    size_t check_index(size_t index) const;
    void check_array_size(const std::vector<double>& values) const;
    container_t m_parameters; //!< collection of fit parameters
    corr_matrix_t m_corr_matrix; //!< correlation matrix
};

#endif // FITPARAMETERSET_H
