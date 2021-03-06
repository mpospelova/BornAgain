// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/BeamItems.h
//! @brief     Defines BeamItem hierarchy
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BEAMITEM_H
#define BEAMITEM_H

#include "SessionItem.h"

class BasicAxisItem;
class Beam;
class FootprintItem;

class BA_CORE_API_ BeamItem : public SessionItem
{
public:
    static const QString P_INTENSITY;
    static const QString P_WAVELENGTH;
    static const QString P_INCLINATION_ANGLE;
    static const QString P_AZIMUTHAL_ANGLE;
    static const QString P_POLARIZATION;

    virtual ~BeamItem();

    double getIntensity() const;
    void setIntensity(double value);

    double getWavelength() const;
    void setWavelength(double value);

    virtual double getInclinationAngle() const = 0;
    virtual void setInclinationAngle(double value);

    double getAzimuthalAngle() const;
    void setAzimuthalAngle(double value);

    std::unique_ptr<Beam> createBeam() const;

protected:
    explicit BeamItem(const QString& beam_model);

    void setInclinationProperty(const QString& inclination_type);
};

class BA_CORE_API_ SpecularBeamItem : public BeamItem
{
public:
    static const QString P_FOOPTPRINT;

    SpecularBeamItem();
    virtual ~SpecularBeamItem();

    double getInclinationAngle() const override;
    void setInclinationAngle(double value) override;

    BasicAxisItem& getInclinationAngleAxis();
    FootprintItem* currentFootprintItem() const;
};

class BA_CORE_API_ GISASBeamItem : public BeamItem
{
public:
    GISASBeamItem();
    virtual ~GISASBeamItem();

    double getInclinationAngle() const override;
};

#endif // BEAMITEM_H

