// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SimulationOptionsItem.cpp
//! @brief     Defines class SimulationOptionsItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include <thread>
#include "SimulationOptionsItem.h"
#include "ComboProperty.h"

namespace
{

QStringList getRunPolicyTooltips()
{
    QStringList result;
    result.append(QStringLiteral("Start simulation immediately, switch to Jobs view automatically when completed"));
    result.append(QStringLiteral("Start simulation immediately, do not switch to Jobs view when completed"));
    result.append(QStringLiteral("Only submit simulation for consequent execution,"
                " has to be started from Jobs view explicitely"));
    return result;
}

const QString tooltip_runpolicy = "Defines run policy for the simulation";
const QString tooltip_nthreads = "Defines number of threads to use for the simulation.";
const QString tooltip_computation =
        "Defines computation method (analytical or Monte-Carlo integration)";
const QString tooltip_ambientmaterial =
        "Define if the material used for Fresnel calculations should be the ambient layer "
        "material or the average material of the layer and the particles it contains";
const QString tooltip_specularpeak =
        "Defines if the specular peak should be included in the simulation result";

}


const QString SimulationOptionsItem::P_RUN_POLICY = "Run Policy";
const QString SimulationOptionsItem::P_NTHREADS = "Number of Threads";
const QString SimulationOptionsItem::P_COMPUTATION_METHOD = "Computation method";
const QString SimulationOptionsItem::P_MC_POINTS = "Number of MC points";
const QString SimulationOptionsItem::P_FRESNEL_MATERIAL_METHOD =
        "Material for Fresnel calculations";
const QString SimulationOptionsItem::P_INCLUDE_SPECULAR_PEAK = "Include specular peak";

SimulationOptionsItem::SimulationOptionsItem()
    : SessionItem(Constants::SimulationOptionsType)
{

    ComboProperty policy;
    policy << Constants::JOB_RUN_IMMEDIATELY
           << Constants::JOB_RUN_IN_BACKGROUND
           << Constants::JOB_RUN_SUBMIT_ONLY;
    policy.setToolTips(getRunPolicyTooltips());
    addProperty(P_RUN_POLICY, policy.variant())->setToolTip(tooltip_runpolicy);

    ComboProperty nthreads;
    nthreads << getCPUUsageOptions();
    addProperty(P_NTHREADS, nthreads.variant())->setToolTip(tooltip_nthreads);

    ComboProperty computationMethod;
    computationMethod << Constants::SIMULATION_ANALYTICAL << Constants::SIMULATION_MONTECARLO;
    addProperty(P_COMPUTATION_METHOD,
                computationMethod.variant())->setToolTip(tooltip_computation);

    addProperty(P_MC_POINTS, 100)->setEnabled(false);

    ComboProperty averageLayerMaterials;
    averageLayerMaterials <<Constants::AMBIENT_LAYER_MATERIAL << Constants::AVERAGE_LAYER_MATERIAL;
    addProperty(P_FRESNEL_MATERIAL_METHOD,
                averageLayerMaterials.variant())->setToolTip(tooltip_ambientmaterial);

    ComboProperty includeSpecularPeak;
    includeSpecularPeak << Constants::No << Constants::Yes;
    addProperty(P_INCLUDE_SPECULAR_PEAK,
                includeSpecularPeak.variant())->setToolTip(tooltip_specularpeak);

    mapper()->setOnPropertyChange(
        [this](const QString &name) {
            if(name == P_COMPUTATION_METHOD && isTag(P_MC_POINTS)) {
                ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();

                if(combo.getValue() == Constants::SIMULATION_ANALYTICAL) {
                    getItem(P_MC_POINTS)->setEnabled(false);

                } else {
                    getItem(P_MC_POINTS)->setEnabled(true);
                }
            }
    });
}

int SimulationOptionsItem::getNumberOfThreads() const
{
    ComboProperty combo = getItemValue(P_NTHREADS).value<ComboProperty>();
	return m_text_to_nthreads[combo.getValue()];
}

bool SimulationOptionsItem::runImmediately() const
{
    return runPolicy() == Constants::JOB_RUN_IMMEDIATELY;
}

bool SimulationOptionsItem::runInBackground() const
{
    return runPolicy() == Constants::JOB_RUN_IN_BACKGROUND;
}

void SimulationOptionsItem::setRunPolicy(const QString &policy)
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    combo.setValue(policy);
    setItemValue(P_RUN_POLICY, combo.variant());
}

void SimulationOptionsItem::setComputationMethod(const QString &name)
{
    ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_COMPUTATION_METHOD, combo.variant());
}

QString SimulationOptionsItem::getComputationMethod() const
{
    ComboProperty combo = getItemValue(P_COMPUTATION_METHOD).value<ComboProperty>();
    return combo.getValue();
}

int SimulationOptionsItem::getNumberOfMonteCarloPoints() const
{
    return getItemValue(P_MC_POINTS).toInt();
}

void SimulationOptionsItem::setNumberOfMonteCarloPoints(int npoints)
{
    setItemValue(P_MC_POINTS, npoints);
}

void SimulationOptionsItem::setFresnelMaterialMethod(const QString& name)
{
    ComboProperty combo = getItemValue(P_FRESNEL_MATERIAL_METHOD).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_FRESNEL_MATERIAL_METHOD, combo.variant());
}

QString SimulationOptionsItem::getFresnelMaterialMethod() const
{
    ComboProperty combo = getItemValue(P_FRESNEL_MATERIAL_METHOD).value<ComboProperty>();
    return combo.getValue();
}

void SimulationOptionsItem::setIncludeSpecularPeak(const QString& name)
{
    ComboProperty combo = getItemValue(P_INCLUDE_SPECULAR_PEAK).value<ComboProperty>();
    combo.setValue(name);
    setItemValue(P_INCLUDE_SPECULAR_PEAK, combo.variant());
}

QString SimulationOptionsItem::getIncludeSpecularPeak() const
{
    ComboProperty combo = getItemValue(P_INCLUDE_SPECULAR_PEAK).value<ComboProperty>();
    return combo.getValue();
}

QString SimulationOptionsItem::runPolicy() const
{
    ComboProperty combo = getItemValue(P_RUN_POLICY).value<ComboProperty>();
    return combo.getValue();
}

//! returns list with number of threads to select
QStringList SimulationOptionsItem::getCPUUsageOptions()
{
	m_text_to_nthreads.clear();
    QStringList result;
    int nthreads = std::thread::hardware_concurrency();
    for(int i = nthreads; i>0; i--){
		QString str;
        if(i == nthreads) {
            str = QString("Max (%1 threads)").arg(QString::number(i));
        } else if(i == 1) {
            str = QString("%1 thread").arg(QString::number(i));
        } else {
            str = QString("%1 threads").arg(QString::number(i));
        }
		result.append(str);
		m_text_to_nthreads[str] = i;
    }
    return result;  
}
