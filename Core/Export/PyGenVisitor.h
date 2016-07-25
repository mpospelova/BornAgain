// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/PyGenVisitor.h
//! @brief     Declares PyGenVisitor class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PYGENVISITOR_H
#define PYGENVISITOR_H

#include "ISampleVisitor.h" // inheriting from
#include <string>

class GISASSimulation;
class SampleLabelHandler;

class BA_CORE_API_ PyGenVisitor
{
public:
    PyGenVisitor(const MultiLayer& multilayer);
    virtual ~PyGenVisitor();

    std::string writePyScript(
        const GISASSimulation* simulation, const std::string& output_filename);
    std::string definePreamble() const;
    std::string defineGetSimulation(const GISASSimulation* simulation) const;
    std::string defineGetSample() const;
    std::string defineMaterials() const;

private:
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleDistributions() const;
    std::string defineParticleCompositions() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string addLayoutsToLayers() const;
    std::string defineMultiLayers() const;
    std::string defineDetector(const GISASSimulation* simulation) const;
    std::string defineDetectorResolutionFunction(const GISASSimulation* simulation) const;
    std::string defineBeam(const GISASSimulation* simulation) const;
    std::string defineParameterDistributions(const GISASSimulation* simulation) const;
    std::string defineMasks(const GISASSimulation* simulation) const;
    std::string defineSimulationOptions(const GISASSimulation* simulation) const;
    std::string definePlotting(const GISASSimulation* simulation) const;
    std::string defineRunSimulation() const;
    SampleLabelHandler* m_label;

    std::string indent() const;
    void setRotationInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
    void setPositionInformation(const IParticle* particle, std::string particle_name,
                                std::ostringstream& result) const;
};

#endif // PYGENVISITOR_H