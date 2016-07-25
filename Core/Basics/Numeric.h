// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Basics/Numeric.h
//! @brief     Declares constants and "almost equal" in namespace Numeric.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef NUMERIC_H
#define NUMERIC_H

#include <limits>

//! Floating-point epsilon, tolerances, almost-equal.

namespace Numeric {

    // TODO move initialization (and #include <limits>) to .cpp
static const double double_epsilon = std::numeric_limits<double>::epsilon();

static const double double_min = std::numeric_limits<double>::min();

//! compare two doubles
bool BA_CORE_API_ areAlmostEqual(double a, double b, double tolerance_factor=1.0);

//! calculates safe relative difference |(a-b)/b|
double BA_CORE_API_ get_relative_difference(double a, double b);

} // Numeric namespace

#endif // NUMERIC_H