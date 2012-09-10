// This file has been generated by Py++.

#include "boost/python.hpp"
#include "BasicVector3D.h"
#include "Experiment.h"
#include "FormFactorCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorPyramid.h"
#include "GISASExperiment.h"
#include "HomogeneousMaterial.h"
#include "IClusteredNanoParticles.h"
#include "ICompositeSample.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "ISample.h"
#include "ISingleton.h"
#include "Lattice.h"
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
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "Transform3D.h"
#include "Units.h"
#include "PythonInterface_free_functions.h"

namespace bp = boost::python;

void register_free_functions(){

    { //::Geometry::CrossProduct
    
        typedef ::Geometry::BasicVector3D< std::complex< double > > ( *CrossProduct_function_type )( ::Geometry::BasicVector3D< std::complex< double > > const,::Geometry::BasicVector3D< std::complex< double > > const );
        
        bp::def( 
            "CrossProduct"
            , CrossProduct_function_type( &::Geometry::CrossProduct )
            , ( bp::arg("vectorLeft"), bp::arg("vectorRight") ) );
    
    }

    { //::Geometry::CrossProduct
    
        typedef ::Geometry::BasicVector3D< double > ( *CrossProduct_function_type )( ::Geometry::BasicVector3D< double > const,::Geometry::BasicVector3D< double > const );
        
        bp::def( 
            "CrossProduct"
            , CrossProduct_function_type( &::Geometry::CrossProduct )
            , ( bp::arg("vectorLeft"), bp::arg("vectorRight") ) );
    
    }

    { //::Geometry::DotProduct
    
        typedef ::std::complex< double > ( *DotProduct_function_type )( ::Geometry::BasicVector3D< std::complex< double > > const,::Geometry::BasicVector3D< std::complex< double > > const );
        
        bp::def( 
            "DotProduct"
            , DotProduct_function_type( &::Geometry::DotProduct )
            , ( bp::arg("left"), bp::arg("right") ) );
    
    }

    { //::Geometry::DotProduct
    
        typedef double ( *DotProduct_function_type )( ::Geometry::BasicVector3D< double > const,::Geometry::BasicVector3D< double > const );
        
        bp::def( 
            "DotProduct"
            , DotProduct_function_type( &::Geometry::DotProduct )
            , ( bp::arg("left"), bp::arg("right") ) );
    
    }

    { //::GetOutputData
    
        typedef ::PyObject * ( *GetOutputData_function_type )( ::GISASExperiment const & );
        
        bp::def( 
            "GetOutputData"
            , GetOutputData_function_type( &::GetOutputData )
            , ( bp::arg("experiment") )
                /* undefined call policies */ );
    
    }

    { //::GetOutputDataAxis
    
        typedef ::PyObject * ( *GetOutputDataAxis_function_type )( ::GISASExperiment const &,int );
        
        bp::def( 
            "GetOutputDataAxis"
            , GetOutputDataAxis_function_type( &::GetOutputDataAxis )
            , ( bp::arg("experiment"), bp::arg("naxis") )
                /* undefined call policies */ );
    
    }

    { //::GetOutputDataNdimensions
    
        typedef int ( *GetOutputDataNdimensions_function_type )( ::GISASExperiment const & );
        
        bp::def( 
            "GetOutputDataNdimensions"
            , GetOutputDataNdimensions_function_type( &::GetOutputDataNdimensions )
            , ( bp::arg("experiment") ) );
    
    }

    { //::Units::deg2rad
    
        typedef double ( *deg2rad_function_type )( double );
        
        bp::def( 
            "deg2rad"
            , deg2rad_function_type( &::Units::deg2rad )
            , ( bp::arg("angle") ) );
    
    }

    { //::Units::rad2deg
    
        typedef double ( *rad2deg_function_type )( double );
        
        bp::def( 
            "rad2deg"
            , rad2deg_function_type( &::Units::rad2deg )
            , ( bp::arg("angle") ) );
    
    }

}
