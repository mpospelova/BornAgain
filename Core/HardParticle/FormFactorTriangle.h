// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTriangle.h
//! @brief     Defines class FormFactorTriangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORTRIANGLE_H
#define FORMFACTORTRIANGLE_H
#include "FormFactorPolyhedron.h"

//! A planar equilateral triangle, for testing form factor computations.

class BA_CORE_API_ FormFactorTriangle : public FormFactorPolygonalSurface
{
public:
    FormFactorTriangle(const double base_edge);

    FormFactorTriangle* clone() const override final { return new FormFactorTriangle(m_base_edge); }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }

protected:
    void onChange() override final;

private:
    double m_base_edge;
};

#endif // FORMFACTORTRIANGLE_H
