// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/src/MinimizerFactory.cpp
//! @brief     Implements class MinimizerFactory.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerFactory.h"
#include "ROOTGSLNLSMinimizer.h"
#include "ROOTGSLSimAnMinimizer.h"
#include "MinimizerTest.h"
#include "MinimizerScan.h"
#include "ROOTMinimizer.h"
#include <boost/assign/list_of.hpp>
#include <iomanip>

MinimizerFactory::Catalogue MinimizerFactory::m_catalogue =
        MinimizerFactory::Catalogue();

// constructing map of minimizer names holding list of defined algorithms
// for every minimizer
MinimizerFactory::Catalogue::Catalogue()
{
    // TODO FIXME As soon as we got rid from ROOT in our dependencies, we've
    // lost Genetic minimizer and it is not easy to get it back

    // our minimizers
    //m_data["Test"]        = boost::assign::list_of("");
    //m_data["Scan"]        = boost::assign::list_of("");
    // ROOT minimizers
    //m_data["Minuit"]      = boost::assign::list_of("Migrad")("Simplex")("Combined")("Scan");
    m_data["Minuit2"]     = boost::assign::list_of("Migrad")("Simplex")("Combined")("Scan")("Fumili");
    //m_data["Fumili"]      = boost::assign::list_of("");
    m_data["GSLMultiMin"] = boost::assign::list_of("ConjugateFR")("ConjugatePR")("BFGS")("BFGS2")("SteepestDescent");
    m_data["GSLMultiFit"] = boost::assign::list_of("");
    m_data["GSLSimAn"]    = boost::assign::list_of("");
    //m_data["Genetic"]     = boost::assign::list_of(""); // available only with ROOT libraries
}


void MinimizerFactory::Catalogue::print(std::ostream& ostr) const
{
    for(MinimizerFactory::Catalogue::const_iterator it=m_data.begin(); it!=m_data.end(); ++it) {
        ostr << std::setw(20) << std::left<< it->first << "  : ";
        for(size_t i=0; i<it->second.size(); ++i ) {
            ostr << it->second[i] << " ";
        }
        ostr << std::endl;
    }
    ostr << std::endl;
}


bool MinimizerFactory::Catalogue::isValid(const std::string& minimizer, const std::string& algorithm) const
{
    // check minimizers names
    MinimizerFactory::Catalogue::const_iterator it = m_data.find(minimizer);
    if(it != m_data.end() ) {
        // check minimizer's algorithm type
        for(size_t i=0; i<it->second.size(); ++i ) if(it->second[i] == algorithm ) return true;
    }
    return false;
}

void MinimizerFactory::printCatalogue()
{
    std::cout << m_catalogue;
}


IMinimizer *MinimizerFactory::createMinimizer(const std::string& minimizer, const std::string& algorithm, const std::string& options)
{
    if( !m_catalogue.isValid(minimizer, algorithm) ) {
        std::ostringstream ostr;
        ostr << "MinimizerFactory::MinimizerFactory() -> Error! Wrong minimizer name. Possible names are:" << std::endl;
        ostr << m_catalogue;
        throw LogicErrorException(ostr.str());
    }

    IMinimizer *result(0);
    if( minimizer == "Test" ) {
        result = new MinimizerTest();
    } else if( minimizer == "Scan" ) {
        result = new MinimizerScan();
    } else {
        result = new ROOTMinimizer(minimizer, algorithm);
    }
    if( !options.empty() ) {
        try {
            result->setOptions(options);
        } catch (NotImplementedException& e) {
            std::cout << "MinimizerFactory::createMinimizer() -> Warning! Minimizer doesn't have method implemented" << e.what() << std::endl;
        }
    }

    return result;
}

