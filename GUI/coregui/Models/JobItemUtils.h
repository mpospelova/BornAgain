// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/JobItemUtils.h
//! @brief     Defines class JobItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef JOBITEMUTILS_H
#define JOBITEMUTILS_H

#include "IDetector.h"
#include <QMap>

class DataItem;
class InstrumentItem;
class JobItem;
class Simulation;

//! Contains set of convenience methods to set data to the IntensityDataItem from domain simulation.
//! Used to modify OutputData's axes units as requested by IntensityDataItem.

namespace JobItemUtils
{

//! Sets simulation results to the JobItem.
BA_CORE_API_ void setResults(JobItem* jobItem, const Simulation* simulation);

//! updates axes of OutputData in IntensityData item
BA_CORE_API_ void updateDataAxes(DataItem* intensityItem,
                                 const InstrumentItem* instrumentItem);

//! loads intensity data from project directory
BA_CORE_API_ void loadIntensityData(DataItem* intensityItem, const QString& projectDir);

//! saves intensity data into project directory
BA_CORE_API_ void saveIntensityData(DataItem* intensityItem, const QString& projectDir);

//! returns axes units names from their domain counterpart
BA_CORE_API_ QString nameFromAxesUnits(AxesUnits units);

//! returns domain axes units type from their GUI name
BA_CORE_API_ AxesUnits axesUnitsFromName(const QString& name);

BA_CORE_API_ void setIntensityItemAxesUnits(DataItem *intensityItem,
                                            const InstrumentItem* instrumentItem);

BA_CORE_API_ void setIntensityItemAxesUnits(DataItem* intensityItem,
                                            const IUnitConverter& converter);

BA_CORE_API_ void createDefaultDetectorMap(DataItem* intensityItem,
                                           const InstrumentItem* instrumentItem);
}

#endif // JOBITEMUTILS_H

