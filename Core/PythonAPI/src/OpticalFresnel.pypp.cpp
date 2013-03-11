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
#include "OpticalFresnel.pypp.h"

namespace bp = boost::python;

struct OpticalFresnel_wrapper : OpticalFresnel, bp::wrapper< OpticalFresnel > {

    OpticalFresnel_wrapper( )
    : OpticalFresnel( )
      , bp::wrapper< OpticalFresnel >(){
        // null constructor
    
    }

    virtual ::ISimulation * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->ISimulation::clone(  );
        }
    }
    
    ::ISimulation * default_clone(  ) const  {
        return ISimulation::clone( );
    }

    virtual void run(  ) {
        if( bp::override func_run = this->get_override( "run" ) )
            func_run(  );
        else{
            this->ISimulation::run(  );
        }
    }
    
    void default_run(  ) {
        ISimulation::run( );
    }

};

void register_OpticalFresnel_class(){

    { //::OpticalFresnel
        typedef bp::class_< OpticalFresnel_wrapper, bp::bases< ISimulation >, boost::noncopyable > OpticalFresnel_exposer_t;
        OpticalFresnel_exposer_t OpticalFresnel_exposer = OpticalFresnel_exposer_t( "OpticalFresnel", bp::init< >() );
        bp::scope OpticalFresnel_scope( OpticalFresnel_exposer );
        bp::class_< OpticalFresnel::FresnelCoeff >( "FresnelCoeff", bp::init< >() )    
            .def( bp::self == bp::self )    
            .def_readwrite( "R", &OpticalFresnel::FresnelCoeff::R )    
            .def_readwrite( "T", &OpticalFresnel::FresnelCoeff::T )    
            .def_readwrite( "X", &OpticalFresnel::FresnelCoeff::X )    
            .def_readwrite( "kz", &OpticalFresnel::FresnelCoeff::kz )    
            .def_readwrite( "r", &OpticalFresnel::FresnelCoeff::r )    
            .def_readwrite( "rb", &OpticalFresnel::FresnelCoeff::rb )    
            .def_readwrite( "t", &OpticalFresnel::FresnelCoeff::t )    
            .def_readwrite( "tb", &OpticalFresnel::FresnelCoeff::tb );
        bp::class_< OpticalFresnel::MultiLayerCoeff >( "MultiLayerCoeff" )    
            .def( 
                "clear"
                , (void ( ::OpticalFresnel::MultiLayerCoeff::* )(  ) )( &::OpticalFresnel::MultiLayerCoeff::clear ) )    
            .def( 
                "__getitem__"
                , (::OpticalFresnel::FresnelCoeff & ( ::OpticalFresnel::MultiLayerCoeff::* )( ::size_t ) )( &::OpticalFresnel::MultiLayerCoeff::operator[] )
                , ( bp::arg("i") )
                , bp::return_internal_reference< >() )    
            .def( 
                "__getitem__"
                , (::OpticalFresnel::FresnelCoeff const & ( ::OpticalFresnel::MultiLayerCoeff::* )( ::size_t ) const)( &::OpticalFresnel::MultiLayerCoeff::operator[] )
                , ( bp::arg("i") )
                , bp::return_value_policy< bp::copy_const_reference >() )    
            .def( 
                "resize"
                , (void ( ::OpticalFresnel::MultiLayerCoeff::* )( ::size_t ) )( &::OpticalFresnel::MultiLayerCoeff::resize )
                , ( bp::arg("size") ) )    
            .def( 
                "size"
                , (::size_t ( ::OpticalFresnel::MultiLayerCoeff::* )(  ) const)( &::OpticalFresnel::MultiLayerCoeff::size ) );
        { //::OpticalFresnel::execute
        
            typedef void ( ::OpticalFresnel::*execute_function_type )( ::MultiLayer const &,::kvector_t const &,::OpticalFresnel::MultiLayerCoeff & ) ;
            
            OpticalFresnel_exposer.def( 
                "execute"
                , execute_function_type( &::OpticalFresnel::execute )
                , ( bp::arg("sample"), bp::arg("k"), bp::arg("coeff") ) );
        
        }
        { //::ISimulation::clone
        
            typedef ::ISimulation * ( ::ISimulation::*clone_function_type )(  ) const;
            typedef ::ISimulation * ( OpticalFresnel_wrapper::*default_clone_function_type )(  ) const;
            
            OpticalFresnel_exposer.def( 
                "clone"
                , clone_function_type(&::ISimulation::clone)
                , default_clone_function_type(&OpticalFresnel_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ISimulation::run
        
            typedef void ( ::ISimulation::*run_function_type )(  ) ;
            typedef void ( OpticalFresnel_wrapper::*default_run_function_type )(  ) ;
            
            OpticalFresnel_exposer.def( 
                "run"
                , run_function_type(&::ISimulation::run)
                , default_run_function_type(&OpticalFresnel_wrapper::default_run) );
        
        }
    }

}
