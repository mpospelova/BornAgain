#include "IsGISAXSTools.h"
#include "Units.h"
#include "Exceptions.h"
#include "MathFunctions.h"

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TStyle.h"
#include "TLine.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <cmath>
#include <algorithm>

double IsGISAXSTools::m_hist_min = 0;
double IsGISAXSTools::m_hist_max = 0;
bool   IsGISAXSTools::m_has_min = false;
bool   IsGISAXSTools::m_has_max = false;


/* ************************************************************************* */
// draw 2D histogram representing logarithm of OutputData (in new canvas)
/* ************************************************************************* */
void IsGISAXSTools::drawLogOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    IsGISAXSTools::setMinimum(1.);
    c1->cd();
    gPad->SetLogz();
    drawOutputDataInPad(output, draw_options, histogram_title);
}

/* ************************************************************************* */
// draw 2D histogram representing OutputData (in new canvas)
/* ************************************************************************* */
void IsGISAXSTools::drawOutputData(const OutputData<double>& output,
        const std::string& canvas_name, const std::string& canvas_title,
        const std::string& draw_options, const std::string &histogram_title)
{
    TCanvas *c1 = new TCanvas(canvas_name.c_str(), canvas_title.c_str(), 0, 0, 1024, 768);
    c1->cd();
    drawOutputDataInPad(output, draw_options, histogram_title);
}

/* ************************************************************************* */
// draw 1D or 2D histograms representing OutputData (in current gPad)
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataInPad(const OutputData<double>& output,
        const std::string& draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataInPad() -> Error! No canvas exists.");
    }

    TH1 *hist(0);
    if(output.getNdimensions() == 2 ) {
        hist = IsGISAXSTools::getOutputDataTH2D(output, "p_hist1D");
    } else {
        hist = IsGISAXSTools::getOutputDataTH123D(output, "p_hist1D");
    }
    hist->SetContour(99);
    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    if( hasMinimum() ) hist->SetMinimum(m_hist_min);
    if( hasMaximum() ) hist->SetMaximum(m_hist_max);
    hist->SetTitle(histogram_title.c_str());
    hist->DrawCopy(draw_options.c_str());
    delete hist;
}


/* ************************************************************************* */
// create TH2D from OutputData
/* ************************************************************************* */
TH2D *IsGISAXSTools::getOutputDataTH2D(const OutputData<double>& output, const std::string &histo_name)
{
    if (output.getNdimensions() !=2) throw( "IsGISAXSTools::getOutputDataTH2D() -> Warning! Expected number of dimensiobs is 2.");

    std::vector<AxisStructure > haxises;
    haxises.resize(output.getNdimensions());

    // we assume variable bin size and prepare [nbins+1] array of left edges of each bin plus right edge of the last bin
    for(size_t i_axis=0; i_axis<output.getNdimensions(); ++i_axis) {
        const AxisDouble *axis = output.getAxis(i_axis);
        if( !axis ) throw("IsGISAXSTools::getOutputDataTH123D() -> Error! Can't cast axis");
        double dx(0);
        haxises[i_axis].nbins = axis->getSize();
        haxises[i_axis].name = axis->getName();
        if( axis->getSize() == 0) {
            throw LogicErrorException("IsGISAXSTools::getOutputDataTH123D() -> Error! Axis with zero size.");
        }else if( axis->getSize() == 1 ) {
            // only one bin, let's invent fake bin size
            dx = 0.1*(*axis)[0];
            haxises[i_axis].xbins.push_back((*axis)[0]-dx/2.);
            haxises[i_axis].xbins.push_back((*axis)[0]+dx/2.);
        }else {
            for(size_t i_bin=0; i_bin<axis->getSize(); ++i_bin) {
                if(i_bin == 0) {
                    dx = (*axis)[1]-(*axis)[0];
                } else {
                    dx = (*axis)[i_bin] - (*axis)[i_bin-1];
                }
                haxises[i_axis].xbins.push_back( (*axis)[i_bin] - dx/2.);
            }
        haxises[i_axis].xbins.push_back((*axis)[axis->getSize()-1] + dx/2.); // right bin edge of last bin, so for 100 bins size of vector will be 101
        }
    }

    // creation of 2D with variable bin size
    TH2D *hist2 = new TH2D(histo_name.c_str(), histo_name.c_str(), (int)haxises[0].nbins, &haxises[0].xbins[0], (int)haxises[1].nbins, &haxises[1].xbins[0]);
    hist2->GetXaxis()->SetTitle( haxises[0].name.c_str() );
    hist2->GetYaxis()->SetTitle( haxises[1].name.c_str() );

    OutputData<double>::const_iterator it = output.begin();
    while (it != output.end())
    {
        double x = output.getValueOfAxis( haxises[0].name.c_str(), it.getIndex() );
        double y = output.getValueOfAxis( haxises[1].name.c_str(), it.getIndex() );
        double value = *it++;
        hist2->Fill(x, y, value);
    }
    hist2->SetContour(50);
    hist2->SetStats(0);
    hist2->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    return hist2;
}



/* ************************************************************************* */
// create TH1D, TH2D or TH3D from OutputData
/* ************************************************************************* */
TH1 *IsGISAXSTools::getOutputDataTH123D(const OutputData<double>& output, const std::string &histo_name)
{
    if (output.getNdimensions() >3) {
        std::cout << "IsGISAXSTools::getOutputDataTH123D() -> Warning! Expected number of dimensions should be not more than 3" << std::endl;
        return 0;
    }

    std::vector<AxisStructure > haxises;
    haxises.resize(output.getNdimensions());

    // we assume variable bin size and prepare [nbins+1] array of left edges of each bin plus right edge of the last bin
    for(size_t i_axis=0; i_axis<output.getNdimensions(); ++i_axis) {
        const AxisDouble *axis = output.getAxis(i_axis);
        if( !axis ) throw("IsGISAXSTools::getOutputDataTH123D() -> Error! Can't cast axis");
        double dx(0);
        haxises[i_axis].nbins = axis->getSize();
        haxises[i_axis].name = axis->getName();
        if( axis->getSize() == 0) {
            throw LogicErrorException("IsGISAXSTools::getOutputDataTH123D() -> Error! Axis with zero size.");
        }else if( axis->getSize() == 1 ) {
            // only one bin, let's invent fake bin size
            dx = 0.1*(*axis)[0];
            haxises[i_axis].xbins.push_back((*axis)[0]-dx/2.);
            haxises[i_axis].xbins.push_back((*axis)[0]+dx/2.);
        }else {
            for(size_t i_bin=0; i_bin<axis->getSize(); ++i_bin) {
                if(i_bin == 0) {
                    dx = (*axis)[1]-(*axis)[0];
                } else {
                    dx = (*axis)[i_bin] - (*axis)[i_bin-1];
                }
                haxises[i_axis].xbins.push_back( (*axis)[i_bin] - dx/2.);
            }
        haxises[i_axis].xbins.push_back((*axis)[axis->getSize()-1] + dx/2.); // right bin edge of last bin, so for 100 bins size of vector will be 101
        }
    }

//    for(size_t i_axis=0; i_axis<output.getNdimensions(); ++i_axis) {
//       std::cout << "axis " << i_axis << " size:" << haxises[i_axis].xbins.size() << std::endl;
//       for(size_t i_bin=0; i_bin<haxises[i_axis].xbins.size(); ++i_bin) {
//           std::cout << haxises[i_axis].xbins[i_bin] << " ";
//       }
//       std::cout << std::endl;
//    }

    // creation of 1D, 2D or 3D histogram with variable bin size
    TH1 *hist(0);
    TH1D *hist1(0);
    TH2D *hist2(0);
    TH3D *hist3(0);
    if(output.getNdimensions() == 1) {
        hist1 = new TH1D(histo_name.c_str(), histo_name.c_str(), (int)haxises[0].nbins, &haxises[0].xbins[0]);
        hist1->GetXaxis()->SetTitle( haxises[0].name.c_str() );
        hist = hist1;
    } else if(output.getNdimensions() == 2) {
        hist2 = new TH2D(histo_name.c_str(), histo_name.c_str(), (int)haxises[0].nbins, &haxises[0].xbins[0], (int)haxises[1].nbins, &haxises[1].xbins[0]);
        hist2->GetXaxis()->SetTitle( haxises[0].name.c_str() );
        hist2->GetYaxis()->SetTitle( haxises[1].name.c_str() );
        hist = hist2;
    } else if(output.getNdimensions() == 3) {
        hist3 = new TH3D(histo_name.c_str(), histo_name.c_str(), (int)haxises[0].nbins, &haxises[0].xbins[0], (int)haxises[1].nbins, &haxises[1].xbins[0], (int)haxises[1].nbins, &haxises[1].xbins[0]);
        hist3->GetXaxis()->SetTitle( haxises[0].name.c_str() );
        hist3->GetYaxis()->SetTitle( haxises[1].name.c_str() );
        hist3->GetZaxis()->SetTitle( haxises[2].name.c_str() );
        hist = hist3;
    } else {
        throw LogicErrorException("IsGISAXSTools::getOutputDataTH123D() -> Error! Wrong number of dimensions.");
    }

    OutputData<double>::const_iterator it = output.begin();
    while (it != output.end())
    {
        std::vector<double > xyz;
        for(size_t i_axis=0; i_axis<haxises.size(); ++i_axis) {
            xyz.push_back(output.getValueOfAxis( haxises[i_axis].name.c_str(), it.getIndex() ) );
        }
        double value = *it++;
        if(hist1) hist1->Fill(xyz[0], value);
        if(hist2) hist2->Fill(xyz[0], xyz[1], value);
        if(hist3) hist3->Fill(xyz[0], xyz[1], xyz[2], value);
    }
    hist->SetContour(50);
    hist->SetStats(0);
    hist->GetYaxis()->SetTitleOffset(1.1);

    gStyle->SetPalette(1);
    gStyle->SetOptStat(0);
    return hist;
}



/* ************************************************************************* */
// draw 1D distribution over values stored in OutputData
// binning of histogram is calculated on the fly
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDistribution1D(const OutputData<double> &output, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDistribution1D() -> Error! No canvas exists.");
    }

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    // creating histogram with automatic binning
    TH1::SetDefaultBufferSize(5000);
    TH1D h1_spect("h1_spect", histo_name.c_str(), 200, 1.0, -1.0); // xmin > xmax as a sign of automatic binning

    OutputData<double>::const_iterator it = output.begin();
    while (it != output.end())
    {
        h1_spect.Fill( *it++ );
    }

    h1_spect.DrawCopy(draw_options.c_str());
}


/* ************************************************************************* */
// draw 1D distribution over relative difference in two OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataDifference1D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference1D() -> Error! No canvas exists.");
    }

    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    *left_clone /= *right_clone;

    std::string histo_name = histogram_title;
    if (histo_name.empty()) {
        histo_name = gPad->GetTitle();
    }

    TH1D h1_spect("difference", histo_name.c_str(), 40, -20.0, 20.0);
    h1_spect.GetXaxis()->SetTitle("log10( (we-isgi)/isgi )");

    OutputData<double>::const_iterator it = left_clone->begin();
    while (it != left_clone->end())
    {
        double x = *it++;
        if(x!=0) {
            x = log10(fabs(x));
        } else {
            // lets put the cases when the difference is exactly 0 to underflow bin
            x = -21.;
        }
        h1_spect.Fill( x );
    }

//    gPad->SetLogy();
    gPad->SetRightMargin(0.115);
    gPad->SetLeftMargin(0.115);
    h1_spect.SetStats(1);
    gStyle->SetOptStat(111111);
    if( hasMinimum() ) h1_spect.SetMinimum(m_hist_min);
    if( hasMaximum() ) h1_spect.SetMaximum(m_hist_max);

    h1_spect.DrawCopy(draw_options.c_str());
    delete left_clone;
    delete right_clone;
}


/* ************************************************************************* */
// draw relative difference of two 2D OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataRelativeDifference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference2D -> Error! No canvas exists.");
    }
    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    *left_clone /= *right_clone;
    left_clone->scaleAll(100.0);

    IsGISAXSTools::drawOutputDataInPad(*left_clone, draw_options, histogram_title);

    delete left_clone;
    delete right_clone;
}


/* ************************************************************************* */
// draw relative chi2 difference of two 2D OutputData sets
/* ************************************************************************* */
void IsGISAXSTools::drawOutputDataChi2Difference2D(const OutputData<double> &left, const OutputData<double> &right, const std::string &draw_options, const std::string &histogram_title)
{
    if(!gPad) {
        throw NullPointerException("IsGISAXSTools::drawOutputDataDifference2D -> Error! No canvas exists.");
    }
    OutputData<double> *left_clone = left.clone();
    OutputData<double> *right_clone = right.clone();

    *left_clone -= *right_clone;
    OutputData<double> *tmp = left_clone->clone();

    *left_clone *= *tmp;
    left_clone->scaleAll(1./left_clone->totalSum());

    IsGISAXSTools::drawOutputDataInPad(*left_clone, draw_options, histogram_title);

    delete left_clone;
    delete right_clone;
    delete tmp;
}


/* ************************************************************************* */
// write output data (1D or 2D) in ASCII file
/* ************************************************************************* */
void IsGISAXSTools::writeOutputDataToFile(const OutputData<double>& output,
        const std::string &filename, int precision)
{
    std::ofstream file;
    file.open(filename.c_str(), std::ios::out);
    if( !file.is_open() ) {
        std::cout << "IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for writing." << std::endl;
        return;
        //throw FileNotIsOpenException("IsGISAXSTools::writeOutputDataToFile() -> Error. Can't open file '"+filename+"' for writing.");
    }
    size_t row_length = output.getAxis(1)->getSize();
    OutputData<double>::const_iterator it = output.begin();
    while(it != output.end()) {
        double z_value = *it++;
        file << std::scientific << std::setprecision(precision) << z_value << "    ";
        if(it.getIndex()%row_length==0) {
            file << std::endl;
        }
    }
    if ( file.bad() ) {
        throw FileIsBadException("IsGISAXSTools::writeOutputDataToFile() -> Error! File is bad, probably it is a directory.");
    }
    file.close();
    std::cout << "IsGISAXSTools::writeOutputDataToFile() -> Info. File '" << filename << "' successfully created." << std::endl;
}


/* ************************************************************************* */
// read data from ASCII file (2D assumed) and fill newly created OutputData with it
/* ************************************************************************* */
OutputData<double> *IsGISAXSTools::readOutputDataFromFile(const std::string &filename, int precision)
{
    // opening ASCII file
    std::ifstream fin;
    fin.open(filename.c_str(), std::ios::in);
    if( !fin.is_open() ) {
        throw FileNotIsOpenException("IsGISAXSTools::readOutputDataFromFile() -> Error. Can't open file '"+filename+"' for reading.");
    }

    typedef std::vector<double > double1d_t;
    typedef std::vector<double1d_t > double2d_t;
    std::string sline;
    double2d_t buff_2d;
    // reading file line by line, every line is parsed into vector of double, so at the end we have buffer_2d of doubles

    while( std::getline(fin, sline))
    {
        // here we mimic different precision in numbers contained in string, if precision is say 6, than 7.2908527770e+03 -> 7.290853e+03
        if(precision > 0) {
            std::string newline;
            std::istringstream is0(sline.c_str());
            double number;
            while( is0 >> number ) {
                std::ostringstream os;
                os << std::scientific << std::setprecision(precision) << number;
                newline += os.str() + std::string("    ");
            }
            sline = newline;
        }

        double1d_t buff_1d;
        std::istringstream iss(sline);
        std::copy(std::istream_iterator<double>(iss), std::istream_iterator<double>(), back_inserter(buff_1d));
        if( buff_1d.empty() ) {
            std::cout << "'" << sline << "'" << std::endl;
            throw LogicErrorException("IsGISAXSTools::readOutputDataFromFile() -> Error. Null size of vector; file: "+filename);
        }
        buff_2d.push_back(buff_1d);
    }
    if ( fin.bad() ) {
        throw FileIsBadException("IsGISAXSTools::readOutputDataFromFile() -> Error! File is bad after readline(), probably it is a directory.");
    }
    fin.close();

    // creating new OutputData and filling it with values from buffer_2d
    int y_size = (int)buff_2d.size();
    int x_size = buff_2d.size() ? (int)buff_2d[0].size() : 0;
    OutputData<double> *p_result = new OutputData<double>;
    p_result->addAxis(std::string("x-axis"), x_size, 0.0, double(x_size));
    p_result->addAxis(std::string("y-axis"), y_size, 0.0, double(y_size));
    p_result->setAllTo(0.0);

    OutputData<double>::iterator it = p_result->begin();
    while (it != p_result->end())
    {
        size_t index_x = p_result->toCoordinates(it.getIndex())[0];
        size_t index_y = p_result->toCoordinates(it.getIndex())[1];
        *it = buff_2d[index_x][index_y];
        ++it;
    }

    return p_result;
}


void IsGISAXSTools::exportOutputDataInVectors2D(const OutputData<double> &output_data
                                        , std::vector<std::vector<double > > &v_data
                                        , std::vector<std::vector<double > > &v_axis0
                                        , std::vector<std::vector<double > > &v_axis1)
{
    if (output_data.getRank() != 2) return;

    const AxisDouble *p_axis0 = output_data.getAxis(0);
    const AxisDouble *p_axis1 = output_data.getAxis(1);
    //std::string axis0_name = p_axis0->getName();
    //std::string axis1_name = p_axis1->getName();
    size_t axis0_size = p_axis0->getSize();
    size_t axis1_size = p_axis1->getSize();

    v_data.clear();
    v_axis0.clear();
    v_axis1.clear();

    v_data.resize(axis0_size);
    v_axis0.resize(axis0_size);
    v_axis1.resize(axis0_size);

    for(size_t i=0; i<axis0_size; ++i) {
        v_data[i].resize(axis1_size,0.0);
        v_axis0[i].resize(axis1_size,0.0);
        v_axis1[i].resize(axis1_size,0.0);
    }

    OutputData<double>::const_iterator it = output_data.begin();
    while (it != output_data.end())
    {
        size_t axis0_index = output_data.toCoordinates(it.getIndex())[0];
        size_t axis1_index = output_data.toCoordinates(it.getIndex())[1];
        double axis0_value = (*p_axis0)[axis0_index];
        double axis1_value = (*p_axis1)[axis1_index];
        double intensity = *it++;

        v_data[axis0_index][axis1_index] = intensity;
        v_axis0[axis0_index][axis1_index] = axis0_value;
        v_axis1[axis0_index][axis1_index] = axis1_value;
    }

}


/* ************************************************************************* */
// Create TLine for displaying of one-dimensional data scan
// OutputData should be 2D, and one of two dimensions should have number of bins == 1
/* ************************************************************************* */
TLine *IsGISAXSTools::getOutputDataScanLine(const OutputData<double> &data)
{
    if(data.getNdimensions() != 2) throw LogicErrorException("IsGISAXSTools::getOutputDataScanLine() -> Error! Number of dimensions should be 2");
    double x1(0), x2(0), y1(0), y2(0);
    if( data.getAxis("alpha_f") && data.getAxis("alpha_f")->getSize() == 1) {
        // horizontal line
        x1 = data.getAxis("phi_f")->getMin();
        x2 = data.getAxis("phi_f")->getMax();
        y1 = y2 = data.getAxis("alpha_f")->getMin();
    }else if( data.getAxis("phi_f") && data.getAxis("phi_f")->getSize() == 1 ) {
        // it's vertical line
        x1 = x2 = data.getAxis("phi_f")->getMin();
        y1 = data.getAxis("alpha_f")->getMin();
        y2 = data.getAxis("alpha_f")->getMax();
    } else {
        throw LogicErrorException("IsGISAXSTools::getOutputDataScanLine() -> Error! Can't handle these axes.");
    }
    TLine *line = new TLine(x1,y1,x2,y2);
    line->SetLineColor(kRed);
    line->SetLineStyle(1);
    line->SetLineWidth(2);
    return line;
}


/* ************************************************************************* */
// Create TH1D for displaying of one-dimensional data scan
// OutputData should be 2D, and one of two dimensions should have number of bins == 1
/* ************************************************************************* */
TH1D *IsGISAXSTools::getOutputDataScanHist(const OutputData<double> &data, const std::string &hname)
{
    if(data.getNdimensions() != 2) throw LogicErrorException("IsGISAXSTools::getOutputDataScanHist() -> Error! Number of dimensions should be 2");
    // one of axis should have dimension 1
    if( (data.getAxis("alpha_f") && data.getAxis("alpha_f")->getSize() != 1) && (data.getAxis("phi_f") && data.getAxis("phi_f")->getSize() != 1))
    {
        throw LogicErrorException("IsGISAXSTools::getOutputDataScanHist() -> Info. Can't create 1D histogram from these axes");
        //std::cout << "IsGISAXSTools::getOutputDataScanHist() -> Info. Can't create 1D histogram from these axes" << std::endl;
        //return 0;
    }

    TH2D *hist2 = IsGISAXSTools::getOutputDataTH2D( data, hname);

    TH1D *hist1(0);
    std::ostringstream ostr_title;
    if( data.getAxis("alpha_f") && data.getAxis("alpha_f")->getSize() == 1) {
        hist1 = hist2->ProjectionX();
        ostr_title << hname << ", alpha_f=" << data.getAxis("alpha_f")->getMin();
    }else if( data.getAxis("phi_f") && data.getAxis("phi_f")->getSize() == 1 ) {
        hist1 = hist2->ProjectionY();
        ostr_title << hname << ", phi_f=" << data.getAxis("phi_f")->getMin();
    } else {
        throw LogicErrorException("IsGISAXSTools::getOutputDataScanHist() -> Error! Unexpected place");
    }
    delete hist2;
    if( !hist1 ) throw LogicErrorException("IsGISAXSTools::getOutputDataScanHist() -> Error! Failed to make projection, existing name?");

    hist1->SetTitle(ostr_title.str().c_str());
    // FIXME remove this trick to bypass weird bug with DrawCopy of TH1D projection of TH1D histograms
    TH1D *h1 = dynamic_cast<TH1D*>(hist1->Clone());
    delete hist1;
    return h1;
}


/* ************************************************************************* */
// add noise to data
/* ************************************************************************* */
OutputData<double > *IsGISAXSTools::createNoisyData(const OutputData<double> &exact_data, double noise_factor)
{
    OutputData<double > *real_data = exact_data.clone();
    OutputData<double>::iterator it = real_data->begin();
    while (it != real_data->end()) {
        double current = *it;
        double sigma = noise_factor*std::sqrt(current);
        double random = MathFunctions::GenerateNormalRandom(current, sigma);
        if (random<0.0) random = 0.0;
        *it = random;
        ++it;
    }
    return real_data;
}


OutputData<double > *IsGISAXSTools::createDataWithGaussianNoise(const OutputData<double> &exact_data, double sigma)
{
    OutputData<double > *real_data = exact_data.clone();
    OutputData<double>::iterator it = real_data->begin();
    while (it != real_data->end()) {
        double current = *it;
        double random = MathFunctions::GenerateNormalRandom(0.0, sigma);
        *it = current+random;
        ++it;
    }
    return real_data;
}

