// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/ParticleCompositionBuilder.h
//! @brief     Defines class ParticleCompositionBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITIONBUILDER_H
#define PARTICLECOMPOSITIONBUILDER_H

#include "ISampleBuilder.h"

//! @class ParticleCompositionBuilder
//! @ingroup standard_samples
//! @brief Builds sample: two layers of spheres at hex lattice

class BA_CORE_API_ ParticleCompositionBuilder : public ISampleBuilder
{
public:
    ParticleCompositionBuilder();
    ISample *buildSample() const;

};

#endif // PARTICLECOMPOSITIONBUILDER_H