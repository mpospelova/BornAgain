// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/LatticeBuilder.h
//! @brief     Defines class Lattice1DBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef LATTICEBUILDER_H
#define LATTICEBUILDER_H

#include "IMultiLayerBuilder.h"

class ISample;

//! Builds sample: cylinders with 1DDL structure factor.
//! @ingroup standard_samples

class BA_CORE_API_ Lattice1DBuilder : public IMultiLayerBuilder
{
public:
    Lattice1DBuilder();
    MultiLayer* buildSample() const;

private:
    double m_length;
    double m_xi;
    double m_corr_length;
    double m_cylinder_height;
    double m_cylinder_radius;
};

#endif // LATTICEBUILDER_H
