// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone6.h
//! @brief     Defines class FormFactorCone6
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORCONE6_H
#define FORMFACTORCONE6_H

#include "FormFactorPolyhedron.h"

//! A frustum (truncated pyramid) with regular hexagonal base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorCone6 : public FormFactorPolyhedron
{
public:
    FormFactorCone6(double base_edge, double height,  double alpha);

    FormFactorCone6* clone() const override final {
        return new FormFactorCone6(m_base_edge, m_height, m_alpha); }
    void accept(INodeVisitor *visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const override final;

    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORCONE6_H
