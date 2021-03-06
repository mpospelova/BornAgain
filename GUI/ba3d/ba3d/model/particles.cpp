// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/particle.cpp
//! @brief     Implements Particle class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "particles.h"
#include <cmath>

namespace RealSpace { namespace Particles {

QString const& name(EShape k)
{
    static QString names[] = {
        "", "FullSphere", "FullSpheroid", "Cylinder", "TruncatedSphere",
        "TruncatedSpheroid", "Cone", "Icosahedron", "Dodecahedron", "TruncatedCube",
        "Prism6", "Cone6", "Pyramid", "Cuboctahedron", "Prism3", "Tetrahedron",
        "EllipsoidalCylinder", "Box", "HemiEllipsoid", "AnisoPyramid",
    };
    return names[uint(k)];
}

//------------------------------------------------------------------------------

using namespace GeometricID;

Particle::Particle(Key key)
    : Object(key)
    , scale(Vector3D::_1)
{}

void Particle::set()
{
    transform(Vector3D::_0, Vector3D::_0);
}

void Particle::transform(Vector3D rotate_, Vector3D translate_)
{
    Object::transform(turn, scale, (rotate = rotate_), offset + (translate = translate_));
}

void Particle::fancy(Vector3D rotate, float r)
{
    Object::transform(turn, scale*r, rotate, offset + translate);
}

//------------------------------------------------------------------------------

static float const pi   = float(M_PI);
static float const pi2f   = float(M_PI_2);
static float const sqrt2f = std::sqrt(2.f);
static float const sqrt3f = std::sqrt(3.f);

// see ~/BornAgain/GUI/ba3d/ba3d/model/geometry/ for BaseShape construction

AnisoPyramid::AnisoPyramid(float L, float W, float H, float alpha)
    : Particle(Key(BaseShape::Column, (1.0f - H/(std::sqrt((L*L/4)+(W*W/4))*std::tan(alpha))), 4))
{
    isNull = (L <= 0 || W <= 0  || H <= 0 || alpha <= 0);
    turn = Vector3D(0,0,45*pi/180.0f);
    scale  = Vector3D(L*sqrt2f, W*sqrt2f, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Box::Box(float L, float W, float H)
    : Particle(Key(BaseShape::Column, 1.0f, 4))
{
    isNull = (L < 0 || W < 0 || H < 0) || (L <= 0 && W <= 0 && H <= 0);
    turn = Vector3D(0,0,45*pi/180.0f);
    scale  = Vector3D(L*sqrt2f, W*sqrt2f, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Cone::Cone(float R, float H, float alpha)
    : Particle(Key(BaseShape::Column, (1.0f - H/(R*std::tan(alpha))), 0))
{
    isNull = (R <= 0 || H <= 0 || alpha <= 0);
    scale  = Vector3D(R*2, R*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Cone6::Cone6(float R, float H, float alpha)
    : Particle(Key(BaseShape::Column, (1.0f - H/(R*std::tan(alpha))), 6))
{
    isNull = (R <= 0 || H <= 0 || alpha <= 0);
    scale  = Vector3D(R*2, R*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Cuboctahedron::Cuboctahedron(float L, float H, float rH, float alpha)
    : Particle(Key(BaseShape::Cuboctahedron, rH, (pi - alpha)))
{
    isNull = (L <= 0 || H <= 0 || rH <= 0 || alpha >= pi2f);
    scale  = Vector3D(L, L, L);
    offset = Vector3D(0, 0, L/2);
    set();
}

Cylinder::Cylinder(float R, float H)
    : Particle(Key(BaseShape::Column, 1.0f, 0))
{
    isNull = (R <= 0 || H <= 0);
    scale  = Vector3D(R*2, R*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Dodecahedron::Dodecahedron(float L)
    : Particle(Key(BaseShape::Dodecahedron))
{
    isNull = (L <= 0);
    float R = L / DodecahedronL2R;
    scale  = Vector3D(R*2, R*2, R*2);
    offset = Vector3D(0, 0, R/std::sqrt(GoldenRatio));
    set();
}

EllipsoidalCylinder::EllipsoidalCylinder(float Ra, float Rb, float H)
    : Particle(Key(BaseShape::Column, 1.0f, 0))
{
    isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
    scale  = Vector3D(Ra*2, Rb*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

FullSphere::FullSphere(float R)
    : Particle(Key(BaseShape::Sphere, 0))
{
    isNull = (R <= 0);
    scale  = Vector3D(R*2);
    offset = Vector3D(0, 0, R);
    set();
}

FullSpheroid::FullSpheroid(float R, float H)
    : Particle(Key(BaseShape::Sphere, 0))
{
    isNull = (R <= 0 || H <= 0);
    scale  = Vector3D(R*2, R*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

HemiEllipsoid::HemiEllipsoid(float Ra, float Rb, float H)
    : Particle(Key(BaseShape::Sphere, .5f))
{
    isNull = (Ra <= 0 || Rb <= 0 || H <= 0);
    scale  = Vector3D(Ra*2, Rb*2, H*2);
    set();
}

Icosahedron::Icosahedron(float L)
    : Particle(Key(BaseShape::Icosahedron))
{
    isNull = (L <= 0);
    float R = L / IcosahedronL2R;
    scale  = Vector3D(R/GoldenRatio, R/GoldenRatio, R/GoldenRatio);
    offset = Vector3D(0, 0, R/(2*GoldenRatio));
    set();
}

Prism3::Prism3(float L, float H)
    : Particle(Key(BaseShape::Column, 1.0f, 3))
{
    isNull = (L <= 0 || H <= 0);
    float D = L*2 / sqrt3f;
    scale = Vector3D(D*2, D*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Prism6::Prism6(float R, float H)
    : Particle(Key(BaseShape::Column, 1.0f, 6))
{
    isNull = (R <= 0 || H <= 0);
    scale  = Vector3D(R*2, R*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Pyramid::Pyramid(float L, float H, float alpha)
    : Particle(Key(BaseShape::Column, (1.0f - H/(std::sqrt(L*L/2)*std::tan(alpha))), 4))
{
    isNull = (L <= 0 || H <= 0 || alpha <= 0);
    float L2 = L * sqrt2f;
    turn = Vector3D(0,0,45*pi/180.0f);
    scale  = Vector3D(L2, L2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

Tetrahedron::Tetrahedron(float L, float H, float alpha)
    : Particle(Key(BaseShape::Column, (1.0f - H/(L/sqrt3f*std::tan(alpha))), 3))
{
    isNull = (L <= 0 || H <= 0 || alpha <= 0);
    float D = L / sqrt3f;
    scale = Vector3D(D*2, D*2, H);
    offset = Vector3D(0, 0, H/2);
    set();
}

TruncatedCube::TruncatedCube(float L, float t)
    : Particle(Key(BaseShape::TruncatedBox, 2*t/L))
{
    isNull = (L <= 0);
    scale  = Vector3D(L,L,L);
    offset = Vector3D(0, 0, L/2);
    set();
}

TruncatedSphere::TruncatedSphere(float R, float H)
    : Particle(Key(BaseShape::Sphere, 1 - H/R/2))
{
    isNull = (R <= 0 || H <= 0);
    scale  = Vector3D(R*2);
    offset = Vector3D(0, 0, H-R);
    set();
}

TruncatedSpheroid::TruncatedSpheroid(float R, float H, float fp)
    : Particle(Key(BaseShape::Sphere, 1 - H/fp/R/2))
{
    isNull = (R <= 0 || H <= 0 || fp <= 0);
    scale  = Vector3D(R*2, R*2, fp*R*2);
    offset = Vector3D(0, 0, H-fp*R);
    set();
}

}}  // namespace RealSpace::Particles
