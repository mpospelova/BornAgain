// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/ISampleBuilder.h
//! @brief     Declares pure virtual base class ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISAMPLEBUILDER_H_
#define ISAMPLEBUILDER_H_

#include "IParameterized.h"

//! @class ISampleBuilder
//! @ingroup simulation_internal
//! @brief Interface to the class capable to build samples to simulate

class BA_CORE_API_ ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder() : IParameterized("SampleBuilder") {}
    virtual ~ISampleBuilder() {}

    virtual class ISample* buildSample() const = 0;

    virtual void init_from(const class FunctionalTestComponentService*) {}
};

#endif // ISAMPLEBUILDER_H_
