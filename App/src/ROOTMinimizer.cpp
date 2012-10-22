#include "ROOTMinimizer.h"
#include "Exceptions.h"
#include "Utils.h"
#include <iomanip>

ROOTMinimizer::ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type) : m_fcn(0)
{
    m_root_minimizer = ROOT::Math::Factory::CreateMinimizer(minimizer_name.c_str(), algo_type.c_str() );
    if( m_root_minimizer == 0 ) {
        throw NullPointerException("ROOTMinimizer::ROOTMinimizer() -> Error! Can't build minimizer");
    }
}


ROOTMinimizer::~ROOTMinimizer()
{
    delete m_root_minimizer;
    delete m_fcn;
}


void ROOTMinimizer::setVariable(int i, const FitParameter *par)
{
    if(par->hasDoubleBound() ) {
        m_root_minimizer->SetLimitedVariable(i, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit(), par->getUpperLimit());
    } else if(par->hasLowerLimit() && !par->hasUpperLimit() ) {
        m_root_minimizer->SetLowerLimitedVariable(i, par->getName().c_str(), par->getValue(), par->getStep(), par->getLowerLimit());
    } else if( par->hasUpperLimit() && !par->hasLowerLimit() ) {
        m_root_minimizer->SetUpperLimitedVariable(i, par->getName().c_str(), par->getValue(), par->getStep(), par->getUpperLimit());
    } else if( !par->hasUpperLimit() && !par->hasLowerLimit() ) {
        m_root_minimizer->SetVariable(i, par->getName().c_str(), par->getValue(), par->getStep());
    } else {
        throw LogicErrorException("ROOTMinimizer::setVariable() -> Strange place... I wish I knew how I got here.");
    }
}



void ROOTMinimizer::minimize()
{
    m_root_minimizer->Minimize();
}


/* ************************************************************************* */
// set fcn function for minimizer
/* ************************************************************************* */
void ROOTMinimizer::setFunction(boost::function<double(const double *)> fcn, int ndim)
{
    m_fcn = new ROOT::Math::Functor(fcn, ndim);
    m_root_minimizer->SetFunction(*m_fcn);
}


/* ************************************************************************* */
// print results
/* ************************************************************************* */
void ROOTMinimizer::printResults() const
{
    std::cout << "ROOTMinimizer::printResults() -> "
    << " NumberOfVariables:" << getNumberOfVariables()
    << " NCall:" << m_root_minimizer->NCalls()
    << " Chi2:" << std::scientific << std::setprecision(8) << getMinValue() << std::endl;

    for(size_t i=0; i<getNumberOfVariables(); ++i) {
        std::cout << "   #" << i
                  << " '" << Utils::AdjustStringLength(m_root_minimizer->VariableName(i), 30) << "' "
                  << " value:" << getValueOfVariableAtMinimum(i)
                  << " error:" << getErrorOfVariable(i) << std::endl;
    }
//    m_root_minimizer->PrintResults();
}


