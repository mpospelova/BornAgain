// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuitePrintObserver.cpp
//! @brief     Implements class FitSuitePrintObserver.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitSuitePrintObserver.h"
#include "FitSuite.h"
#include "FitParameterSet.h"
#include "FitSuiteStrategies.h"
#include "MinimizerUtils.h"
#include "IFitParameter.h"
#include "FitSuiteUtils.h"
#include <iostream>
#include <iomanip>

FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth)
    : IFitObserver(print_every_nth)
    , m_fit_suite(0)
{
}

void FitSuitePrintObserver::update(FitSuite* fit_suite)
{
    m_fit_suite = fit_suite;

    if(fit_suite->numberOfIterations() == 0) {
        m_run_time.start();
        m_last_call_time.start();
        printFitSuiteHeader();
    }

    if(m_strategy_has_changed) {
        std::cout << MinimizerUtils::sectionString() << "\n";
        std::cout << (*m_fit_suite->fitStrategies()->currentStrategy()) << std::endl;
        std::cout << MinimizerUtils::sectionString() << "\n";
    }

    printIterationHeader();
    printWallTime();
    printParameters();

    if(fit_suite->isLastIteration())
        printFitResults();
}

void FitSuitePrintObserver::printFitSuiteHeader()
{
    std::cout << MinimizerUtils::sectionString("Fit parameter settings");
    std::cout << FitSuiteUtils::fitParameterSettingsToString(*m_fit_suite->fitParameters());
    std::cout << MinimizerUtils::sectionString();
}

void FitSuitePrintObserver::printIterationHeader()
{
    std::cout << "FitPrintObserver::update() -> Info."
              << " NCall:" << m_fit_suite->numberOfIterations()
              << " NStrategy:" << m_fit_suite->currentStrategyIndex()
              << " Chi2:" << std::scientific << std::setprecision(8)
              << m_fit_suite->getChi2() << std::endl;
}

void FitSuitePrintObserver::printWallTime()
{
    m_last_call_time.stop();
    std::cout << "Wall time since last call:" << std::fixed << std::setprecision(2)
              << m_last_call_time.runTime() << std::endl;
    m_last_call_time.start();
}

void FitSuitePrintObserver::printParameters()
{
    for(auto par : *m_fit_suite->fitParameters())
        std::cout << "   # " << par->toString() << "\n";
}

void FitSuitePrintObserver::printFitResults()
{
    std::cout << "This was the last iteration." << std::endl;
    m_run_time.stop();
    m_fit_suite->printResults();
    std::cout << "Total time spend: " << std::fixed << std::setprecision(2)
              << m_run_time.runTime() << " sec." <<std::endl;
    std::cout << std::endl;
}
