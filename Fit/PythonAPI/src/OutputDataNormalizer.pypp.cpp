// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonFitList.h"
#include "OutputDataNormalizer.pypp.h"

namespace bp = boost::python;

struct OutputDataNormalizer_wrapper : OutputDataNormalizer, bp::wrapper< OutputDataNormalizer > {

    OutputDataNormalizer_wrapper(OutputDataNormalizer const & arg )
    : OutputDataNormalizer( arg )
      , bp::wrapper< OutputDataNormalizer >(){
        // copy constructor
        
    }

    OutputDataNormalizer_wrapper(double scale=1.0e+0, double shift=0.0 )
    : OutputDataNormalizer( scale, shift )
      , bp::wrapper< OutputDataNormalizer >(){
        // constructor
    
    }

    virtual ::OutputDataNormalizer * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->OutputDataNormalizer::clone(  );
    }
    
    
    ::OutputDataNormalizer * default_clone(  ) const  {
        return OutputDataNormalizer::clone( );
    }

    virtual ::OutputData< double > * createNormalizedData( ::OutputData< double > const & data ) const  {
        if( bp::override func_createNormalizedData = this->get_override( "createNormalizedData" ) )
            return func_createNormalizedData( boost::ref(data) );
        else
            return this->OutputDataNormalizer::createNormalizedData( boost::ref(data) );
    }
    
    
    ::OutputData< double > * default_createNormalizedData( ::OutputData< double > const & data ) const  {
        return OutputDataNormalizer::createNormalizedData( boost::ref(data) );
    }

    virtual void setMaximumIntensity( double max_intensity ) {
        if( bp::override func_setMaximumIntensity = this->get_override( "setMaximumIntensity" ) )
            func_setMaximumIntensity( max_intensity );
        else
            this->OutputDataNormalizer::setMaximumIntensity( max_intensity );
    }
    
    
    void default_setMaximumIntensity( double max_intensity ) {
        OutputDataNormalizer::setMaximumIntensity( max_intensity );
    }

};

void register_OutputDataNormalizer_class(){

    { //::OutputDataNormalizer
        typedef bp::class_< OutputDataNormalizer_wrapper, bp::bases< IOutputDataNormalizer > > OutputDataNormalizer_exposer_t;
        OutputDataNormalizer_exposer_t OutputDataNormalizer_exposer = OutputDataNormalizer_exposer_t( "OutputDataNormalizer", bp::init< bp::optional< double, double > >(( bp::arg("scale")=1.0e+0, bp::arg("shift")=0.0 )) );
        bp::scope OutputDataNormalizer_scope( OutputDataNormalizer_exposer );
        { //::OutputDataNormalizer::clone
        
            typedef ::OutputDataNormalizer * ( ::OutputDataNormalizer::*clone_function_type )(  ) const;
            typedef ::OutputDataNormalizer * ( OutputDataNormalizer_wrapper::*default_clone_function_type )(  ) const;
            
            OutputDataNormalizer_exposer.def( 
                "clone"
                , clone_function_type(&::OutputDataNormalizer::clone)
                , default_clone_function_type(&OutputDataNormalizer_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OutputDataNormalizer::createNormalizedData
        
            typedef ::OutputData< double > * ( ::OutputDataNormalizer::*createNormalizedData_function_type )( ::OutputData< double > const & ) const;
            typedef ::OutputData< double > * ( OutputDataNormalizer_wrapper::*default_createNormalizedData_function_type )( ::OutputData< double > const & ) const;
            
            OutputDataNormalizer_exposer.def( 
                "createNormalizedData"
                , createNormalizedData_function_type(&::OutputDataNormalizer::createNormalizedData)
                , default_createNormalizedData_function_type(&OutputDataNormalizer_wrapper::default_createNormalizedData)
                , ( bp::arg("data") )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OutputDataNormalizer::setMaximumIntensity
        
            typedef void ( ::OutputDataNormalizer::*setMaximumIntensity_function_type )( double ) ;
            typedef void ( OutputDataNormalizer_wrapper::*default_setMaximumIntensity_function_type )( double ) ;
            
            OutputDataNormalizer_exposer.def( 
                "setMaximumIntensity"
                , setMaximumIntensity_function_type(&::OutputDataNormalizer::setMaximumIntensity)
                , default_setMaximumIntensity_function_type(&OutputDataNormalizer_wrapper::default_setMaximumIntensity)
                , ( bp::arg("max_intensity") ) );
        
        }
    }

}
