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
#include "IDecoration.pypp.h"

namespace bp = boost::python;

struct IDecoration_wrapper : IDecoration, bp::wrapper< IDecoration > {

    IDecoration_wrapper( )
    : IDecoration( )
      , bp::wrapper< IDecoration >(){
        // null constructor
    
    }

    virtual ::IDecoration * clone(  ) const {
        bp::override func_clone = this->get_override( "clone" );
        return func_clone(  );
    }

    virtual double getAbundanceFractionOfParticle( ::size_t index ) const {
        bp::override func_getAbundanceFractionOfParticle = this->get_override( "getAbundanceFractionOfParticle" );
        return func_getAbundanceFractionOfParticle( index );
    }

    virtual ::SafePointerVector< IInterferenceFunction > getInterferenceFunctions(  ) const {
        bp::override func_getInterferenceFunctions = this->get_override( "getInterferenceFunctions" );
        return func_getInterferenceFunctions(  );
    }

    virtual ::size_t getNumberOfInterferenceFunctions(  ) const  {
        if( bp::override func_getNumberOfInterferenceFunctions = this->get_override( "getNumberOfInterferenceFunctions" ) )
            return func_getNumberOfInterferenceFunctions(  );
        else{
            return this->IDecoration::getNumberOfInterferenceFunctions(  );
        }
    }
    
    ::size_t default_getNumberOfInterferenceFunctions(  ) const  {
        return IDecoration::getNumberOfInterferenceFunctions( );
    }

    virtual ::size_t getNumberOfParticles(  ) const {
        bp::override func_getNumberOfParticles = this->get_override( "getNumberOfParticles" );
        return func_getNumberOfParticles(  );
    }

    virtual ::ParticleInfo const * getParticleInfo( ::size_t index ) const {
        bp::override func_getParticleInfo = this->get_override( "getParticleInfo" );
        return func_getParticleInfo( index );
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

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
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

    virtual void print_structure(  ) {
        if( bp::override func_print_structure = this->get_override( "print_structure" ) )
            func_print_structure(  );
        else{
            this->ISample::print_structure(  );
        }
    }
    
    void default_print_structure(  ) {
        ISample::print_structure( );
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

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_IDecoration_class(){

    bp::class_< IDecoration_wrapper, bp::bases< ICompositeSample >, boost::noncopyable >( "IDecoration", bp::init< >() )    
        .def( 
            "clone"
            , bp::pure_virtual( (::IDecoration * ( ::IDecoration::* )(  ) const)(&::IDecoration::clone) )
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getAbundanceFractionOfParticle"
            , bp::pure_virtual( (double ( ::IDecoration::* )( ::size_t ) const)(&::IDecoration::getAbundanceFractionOfParticle) )
            , ( bp::arg("index") ) )    
        .def( 
            "getInterferenceFunctions"
            , bp::pure_virtual( (::SafePointerVector< IInterferenceFunction > ( ::IDecoration::* )(  ) const)(&::IDecoration::getInterferenceFunctions) ) )    
        .def( 
            "getNumberOfInterferenceFunctions"
            , (::size_t ( ::IDecoration::* )(  ) const)(&::IDecoration::getNumberOfInterferenceFunctions)
            , (::size_t ( IDecoration_wrapper::* )(  ) const)(&IDecoration_wrapper::default_getNumberOfInterferenceFunctions) )    
        .def( 
            "getNumberOfParticles"
            , bp::pure_virtual( (::size_t ( ::IDecoration::* )(  ) const)(&::IDecoration::getNumberOfParticles) ) )    
        .def( 
            "getParticleInfo"
            , bp::pure_virtual( (::ParticleInfo const * ( ::IDecoration::* )( ::size_t ) const)(&::IDecoration::getParticleInfo) )
            , ( bp::arg("index") )
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getTotalParticleSurfaceDensity"
            , (double ( ::IDecoration::* )(  ) const)( &::IDecoration::getTotalParticleSurfaceDensity ) )    
        .def( 
            "setTotalParticleSurfaceDensity"
            , (void ( ::IDecoration::* )( double ) )( &::IDecoration::setTotalParticleSurfaceDensity )
            , ( bp::arg("surface_density") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( IDecoration_wrapper::* )(  ) )(&IDecoration_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( IDecoration_wrapper::* )(  ) const)(&IDecoration_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample * ( ::ICompositeSample::* )(  ) )(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample * ( IDecoration_wrapper::* )(  ) )(&IDecoration_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample const * ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample const * ( IDecoration_wrapper::* )(  ) const)(&IDecoration_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( IDecoration_wrapper::* )(  ) const)(&IDecoration_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( IDecoration_wrapper::* )(  ) )(&IDecoration_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( IDecoration_wrapper::* )(  ) )(&IDecoration_wrapper::default_setParametersAreChanged) )    
        .def( 
            "size"
            , (::size_t ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::size)
            , (::size_t ( IDecoration_wrapper::* )(  ) const)(&IDecoration_wrapper::default_size) );

}
