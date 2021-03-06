// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuitePrintObserver.h
//! @brief     Defines class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FITSUITEPRINTOBSERVER_H
#define FITSUITEPRINTOBSERVER_H

#include "IFitObserver.h"
#include "TimeInterval.h"

//! Prints fit progress at the end of each FitSuite's iteration.
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuitePrintObserver : public IFitObserver
{
public:
    FitSuitePrintObserver(int print_every_nth = 1);
    virtual ~FitSuitePrintObserver() {}

    void update(FitSuite* fit_suite);

protected:
    void printFitSuiteHeader();
    void printIterationHeader();
    void printWallTime();
    void printParameters();
    void printFitResults();

    FitSuite* m_fit_suite;
    TimeInterval m_run_time;
    TimeInterval m_last_call_time;
};

#endif // FITSUITEPRINTOBSERVER_H
