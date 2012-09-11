#include "DWBASimulation.h"

DWBASimulation::DWBASimulation()
: m_alpha_i(0)
{
}

DWBASimulation::~DWBASimulation()
{
}

void DWBASimulation::init(const Experiment& experiment)
{
    m_dwba_intensity.clear();
    Detector detector = experiment.getDetector();
    size_t detector_dimension = detector.getDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim) {
        m_dwba_intensity.addAxis(new NamedVector<double>(detector.getAxis(dim)));
    }
    Beam beam = experiment.getBeam();
    m_ki = beam.getCentralK();
    kvector_t ki_real(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    m_alpha_i = std::asin(ki_real.z()/ki_real.mag());
}

double DWBASimulation::getWaveLength() const
{
    kvector_t real_ki(m_ki.x().real(), m_ki.y().real(), m_ki.z().real());
    return 2.0*M_PI/real_ki.mag();
}
