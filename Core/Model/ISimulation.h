// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/ISimulation.h
//! @brief     Defines and implements interface class ISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ISIMULATION_H
#define ISIMULATION_H

#include "ICloneable.h"
#include "WinDllMacros.h"
#include <string>

//! Completion status of a numeric computation.
//! Pure virtual base class for our model evaluation routines.
//! Currently, the only child is DWBASimulations, which is the base for some more classes.
//! @ingroup algorithms_internal

class BA_CORE_API_ ISimulation : ICloneable
{
public:
    enum ESimulationStatus { IDLE, RUNNING, COMPLETED, FAILED };

    ISimulation() : m_status(IDLE) {}
    virtual ~ISimulation() {}
    virtual ISimulation* clone() const =0;

    virtual void run() =0;

    bool isCompleted() const { return m_status == COMPLETED; }

    std::string getRunMessage() const { return m_run_message; }

protected:
    virtual void runProtected() =0;

    void setStatus(ESimulationStatus status) { m_status = status; }

    void setRunMessage(const std::string& message) { m_run_message = message; }

    ESimulationStatus m_status;
    std::string m_run_message;
};

#endif // ISIMULATION_H
