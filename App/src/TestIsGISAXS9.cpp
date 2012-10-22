#include "TestIsGISAXS9.h"
#include "IsGISAXSTools.h"
#include "Units.h"
#include "Utils.h"
#include "MultiLayer.h"
#include "GISASExperiment.h"
#include "SampleFactory.h"
#include "DrawHelper.h"

#include "TCanvas.h"


TestIsGISAXS9::TestIsGISAXS9()  : IFunctionalTest("TestIsGISAXS9")
{
}

TestIsGISAXS9::~TestIsGISAXS9()
{
    clear();
}


void TestIsGISAXS9::clear()
{
    for(std::vector<OutputData<double> *>::iterator it=m_results.begin(); it!=m_results.end(); it++) {
        delete (*it);
    }
    m_results.clear();
}


void TestIsGISAXS9::execute()
{
    clear();

    // setting experiment
    GISASExperiment experiment(mp_options);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);

    // pyramid
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS9_Pyramid"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    OutputData<double> *data = experiment.getOutputDataClone();
    m_results.push_back( data );
    IsGISAXSTools::writeOutputDataToFile(*m_results.back(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z0.ima");

    // rotated pyramid
    sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS9_RotatedPyramid"));
    experiment.setSample(*sample);
    experiment.runSimulation();
    data = experiment.getOutputDataClone();
    m_results.push_back( data );
    IsGISAXSTools::writeOutputDataToFile(*m_results.back(), Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z45.ima");

}


void TestIsGISAXS9::finalise()
{
    std::vector<std::string > isgi_files;
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/isgi_pyramid_Z0.ima");
    isgi_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/isgi_pyramid_Z45.ima");

    std::vector<std::string > this_files;
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z0.ima");
    this_files.push_back(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-9/this_pyramid_Z45.ima");

    int ncomparison = m_results.size();

    TCanvas *canvaces[2];
    canvaces[0] = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS9_c1", "Pyramid DWBA formfactor");
    canvaces[1] = DrawHelper::instance().createAndRegisterCanvas("TestIsGISAXS9_c2", "Pyramid DWBA formfactor");

    for(int i_comparison=0; i_comparison<ncomparison; i_comparison++) {
        OutputData<double> *isgi_data = IsGISAXSTools::readOutputDataFromFile(isgi_files[i_comparison], 10);
        OutputData<double> *our_data = IsGISAXSTools::readOutputDataFromFile(this_files[i_comparison], 10);

        TCanvas *c1 = canvaces[i_comparison];
        c1->Divide(2,2);

        IsGISAXSTools::setMinimum(1.);
        // our calculations
        c1->cd(1); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*our_data, "CONT4 Z", "Our pyramid FF");

        // isgisaxs data
        c1->cd(2); gPad->SetLogz();
        IsGISAXSTools::drawOutputDataInPad(*isgi_data, "CONT4 Z", "IsGisaxs pyramid FF");

        // difference
        c1->cd(3);
        IsGISAXSTools::setMinimum(-0.0001);
        IsGISAXSTools::setMaximum(0.0001);
        IsGISAXSTools::drawOutputDataRelativeDifference2D(*our_data, *isgi_data, "CONT4 Z", "2D Difference map");

        // difference
        c1->cd(4);
        IsGISAXSTools::resetMinimumAndMaximum();
        IsGISAXSTools::setMinimum(1);
        IsGISAXSTools::drawOutputDataDifference1D(*our_data, *isgi_data, "", "Difference spectra");

        delete isgi_data;

        IsGISAXSTools::resetMinimum(); IsGISAXSTools::resetMaximum();
    }
}
