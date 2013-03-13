// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Bin.h"
#include "Crystal.h"
#include "DiffuseParticleInfo.h"
#include "FTDistributions.h"
#include "FormFactorBox.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorParallelepiped.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Instrument.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "Lattice2DIFParameters.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "Lattice2DIFParameters.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "ParticleDecoration.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "IStochasticParameter.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Transform3D.h"
#include "Types.h"
#include "Units.h"
#include "IParameterized.pypp.h"

namespace bp = boost::python;

struct IParameterized_wrapper : IParameterized, bp::wrapper< IParameterized > {

    IParameterized_wrapper( )
    : IParameterized( )
      , bp::wrapper< IParameterized >(){
        // null constructor
    
    }

    IParameterized_wrapper(::std::string const & name )
    : IParameterized( name )
      , bp::wrapper< IParameterized >(){
        // constructor
    
    }

    IParameterized_wrapper(::IParameterized const & other )
    : IParameterized( boost::ref(other) )
      , bp::wrapper< IParameterized >(){
        // copy constructor
    
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_IParameterized_class(){

    { //::IParameterized
        typedef bp::class_< IParameterized_wrapper > IParameterized_exposer_t;
        IParameterized_exposer_t IParameterized_exposer = IParameterized_exposer_t( "IParameterized", bp::init< >() );
        bp::scope IParameterized_scope( IParameterized_exposer );
        IParameterized_exposer.def( bp::init< std::string const & >(( bp::arg("name") )) );
        IParameterized_exposer.def( bp::init< IParameterized const & >(( bp::arg("other") )) );
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( IParameterized_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            IParameterized_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&IParameterized_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( IParameterized_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            IParameterized_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&IParameterized_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::getParameterPool
        
            typedef ::ParameterPool * ( ::IParameterized::*getParameterPool_function_type )(  ) ;
            
            IParameterized_exposer.def( 
                "getParameterPool"
                , getParameterPool_function_type( &::IParameterized::getParameterPool )
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::IParameterized::operator=
        
            typedef ::IParameterized & ( ::IParameterized::*assign_function_type )( ::IParameterized const & ) ;
            
            IParameterized_exposer.def( 
                "assign"
                , assign_function_type( &::IParameterized::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( IParameterized_wrapper::*default_printParameters_function_type )(  ) const;
            
            IParameterized_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&IParameterized_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( IParameterized_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            IParameterized_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&IParameterized_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
