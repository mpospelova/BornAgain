// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/CoreSpecialTestFactory.cpp
//! @brief     Implements CoreSpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "CoreSpecialTestFactory.h"
#include "BatchSimulation.h"
#include "DetectorTest.h"
#include "PolDWBAMagCylinders.h"
#include "CoreIOTest.h"
#include "FourierTransformationTest.h"
#include "MesoCrystalPerformanceTest.h"

CoreSpecialTestFactory::CoreSpecialTestFactory()
{
    registerItem("BatchSimulation",
                 create_new<BatchSimulation>,
                 "Running GISASSimulation in batch mode");

    registerItem("PolDWBAMagCylinders",
                 create_new<PolDWBAMagCylinders>,
                 "Special test for polarized materials");

    registerItem("CoreIO",
                 create_new<CoreIOTest>,
                 "Input/output of heavy files");

    registerItem("DetectorTest",
                 create_new<DetectorTest>,
                 "Performance on set of detectors of different size");

    registerItem("FourierTransformation",
                 create_new<FourierTransformationTest>,
                 "Fourier transformation of GISAS images");

    registerItem("MesoPerformance",
                 create_new<MesoCrystalPerformanceTest>,
                 "Heavy mesocrystal simulation");
}
