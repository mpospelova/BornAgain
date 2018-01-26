// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialDataItems.h
//! @brief     Defines MaterialDataItems classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MATERIALDATAITEMS_H
#define MATERIALDATAITEMS_H

#include "SessionItem.h"

class BA_CORE_API_ MaterialDataItem : public SessionItem
{
protected:
    MaterialDataItem(const QString& modelType);
};

class BA_CORE_API_ MaterialRefractiveDataItem : public MaterialDataItem
{
public:
    static const QString P_DELTA;
    static const QString P_BETA;

    MaterialRefractiveDataItem();

    double delta() const;
    void setDelta(double delta);

    double beta() const;
    void setBeta(double beta);

private:
    void updateLabel();
};

class BA_CORE_API_ MaterialSLDDataItem : public MaterialDataItem
{
public:
    static const QString P_SLD;
    static const QString P_ABS_TERM;

    MaterialSLDDataItem();
};

#endif // MATERIALDATAITEMS_H
