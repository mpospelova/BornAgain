// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorBox.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "FTDistributions.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "Lattice2DIFParameters.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "Crystal.h"
#include "ParticleDecoration.h"
#include "ParticleBuilder.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "PositionParticleInfo.h"
#include "ParticleInfo.h"
#include "DiffuseParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "Transform3D.h"
#include "Units.h"
#include "Types.h"
#include "MultiLayerDWBASimulation.pypp.h"

namespace bp = boost::python;

struct MultiLayerDWBASimulation_wrapper : MultiLayerDWBASimulation, bp::wrapper< MultiLayerDWBASimulation > {

    virtual ::MultiLayerDWBASimulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->MultiLayerDWBASimulation::clone(  );
        }
    }
    
    ::MultiLayerDWBASimulation * default_clone(  ) const  {
        return MultiLayerDWBASimulation::clone( );
    }

    virtual void init( ::Simulation const & simulation ) {
        if( bp::override func_init = this->get_override( "init" ) )
            func_init( boost::ref(simulation) );
        else{
            this->MultiLayerDWBASimulation::init( boost::ref(simulation) );
        }
    }
    
    void default_init( ::Simulation const & simulation ) {
        MultiLayerDWBASimulation::init( boost::ref(simulation) );
    }

    virtual void run(  ) {
        if( bp::override func_run = this->get_override( "run" ) )
            func_run(  );
        else{
            this->MultiLayerDWBASimulation::run(  );
        }
    }
    
    void default_run(  ) {
        MultiLayerDWBASimulation::run( );
    }

    virtual void setThreadInfo( ::ThreadInfo const & thread_info ) {
        if( bp::override func_setThreadInfo = this->get_override( "setThreadInfo" ) )
            func_setThreadInfo( boost::ref(thread_info) );
        else{
            this->MultiLayerDWBASimulation::setThreadInfo( boost::ref(thread_info) );
        }
    }
    
    void default_setThreadInfo( ::ThreadInfo const & thread_info ) {
        MultiLayerDWBASimulation::setThreadInfo( boost::ref(thread_info) );
    }

};

void register_MultiLayerDWBASimulation_class(){

    bp::class_< MultiLayerDWBASimulation_wrapper, boost::noncopyable >( "MultiLayerDWBASimulation", bp::no_init )    
        .def( 
            "clone"
            , (::MultiLayerDWBASimulation * ( ::MultiLayerDWBASimulation::* )(  ) const)(&::MultiLayerDWBASimulation::clone)
            , (::MultiLayerDWBASimulation * ( MultiLayerDWBASimulation_wrapper::* )(  ) const)(&MultiLayerDWBASimulation_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "init"
            , (void ( ::MultiLayerDWBASimulation::* )( ::Simulation const & ) )(&::MultiLayerDWBASimulation::init)
            , (void ( MultiLayerDWBASimulation_wrapper::* )( ::Simulation const & ) )(&MultiLayerDWBASimulation_wrapper::default_init)
            , ( bp::arg("simulation") ) )    
        .def( 
            "run"
            , (void ( ::MultiLayerDWBASimulation::* )(  ) )(&::MultiLayerDWBASimulation::run)
            , (void ( MultiLayerDWBASimulation_wrapper::* )(  ) )(&MultiLayerDWBASimulation_wrapper::default_run) )    
        .def( 
            "setThreadInfo"
            , (void ( ::MultiLayerDWBASimulation::* )( ::ThreadInfo const & ) )(&::MultiLayerDWBASimulation::setThreadInfo)
            , (void ( MultiLayerDWBASimulation_wrapper::* )( ::ThreadInfo const & ) )(&MultiLayerDWBASimulation_wrapper::default_setThreadInfo)
            , ( bp::arg("thread_info") ) );

}
