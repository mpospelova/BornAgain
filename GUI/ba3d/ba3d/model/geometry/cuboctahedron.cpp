// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry/cuboctahedron.cpp
//! @brief     Implements utility functions in ba3d namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "../geometry.h"
#include <qmath.h>

namespace RealSpace {

Geometry::Mesh Geometry::meshCuboctahedron(float rH, float beta) { // t/D

    // beta is the angle between the absolute base of the shape (NOT the common square base)
    // and a side face. In terms of alpha (angle with common square base), it is (PI-alpha) radians

    Q_ASSERT(beta >= float(M_PI_2));
    Q_ASSERT(rH >= 0);

    float const D = .5f, H = 2*D / (rH + 1), t = tanf(beta - float(M_PI_2));
    float const Db = D - t*H, Dt = D - t*(2*D - H);

    Vertices vs_; vs_.reserve(12);
    float z[] = {-D, H-D, +D}, d[] = {Db, D, Dt};
    for(int i=0; i<3; ++i)
        for (int x : {-1, +1})
            for (int y : {-1, +1}) {
                float di = d[i];
                vs_.append(Vector3D(x*di, y*di, z[i]));
            }

    Q_ASSERT(12 == vs_.count());

    Vertices vs; vs.reserve(60);

    vs.addQuad(vs_, 0,  1,  3, 2);
    vs.addQuad(vs_, 8, 10, 11, 9);
    vs.addQuad(vs_, 0,  4,  5, 1);
    vs.addQuad(vs_, 1,  5,  7, 3);
    vs.addQuad(vs_, 3,  7,  6, 2);
    vs.addQuad(vs_, 2,  6,  4, 0);
    vs.addQuad(vs_, 4,  8,  9, 5);
    vs.addQuad(vs_, 5,  9, 11, 7);
    vs.addQuad(vs_, 7, 11, 10, 6);
    vs.addQuad(vs_, 6, 10,  8, 4);

    Q_ASSERT(60 == vs.count());

    return makeMesh(vs);
}

}  // namespace RealSpace
