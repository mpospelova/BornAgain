// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Python/PyEmbedded/PyEmbeddedTestFactory.cpp
//! @brief     Implements PyEmbeddedTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyEmbeddedTestFactory.h"
#include "TestCases.h"

PyEmbeddedTestFactory::PyEmbeddedTestFactory()
{
    registerItem("FunctionCall",
                 create_new<FunctionCall>,
                 "Calling function from embedded Python");
    registerItem("MethodCall",
                  create_new<MethodCall>,
                  "Creating object embedded and calling its methods.");
}
