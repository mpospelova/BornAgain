// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "FTDistribution1DGauss.pypp.h"

namespace bp = boost::python;

struct FTDistribution1DGauss_wrapper : FTDistribution1DGauss, bp::wrapper< FTDistribution1DGauss > {

    FTDistribution1DGauss_wrapper(FTDistribution1DGauss const & arg )
    : FTDistribution1DGauss( arg )
      , bp::wrapper< FTDistribution1DGauss >(){
        // copy constructor
        
    }

    FTDistribution1DGauss_wrapper(double omega )
    : FTDistribution1DGauss( omega )
      , bp::wrapper< FTDistribution1DGauss >(){
        // constructor
    
    }

    virtual ::FTDistribution1DGauss * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else
            return this->FTDistribution1DGauss::clone(  );
    }
    
    
    ::FTDistribution1DGauss * default_clone(  ) const  {
        return FTDistribution1DGauss::clone( );
    }

    virtual double evaluate( double q ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( q );
        else
            return this->FTDistribution1DGauss::evaluate( q );
    }
    
    
    double default_evaluate( double q ) const  {
        return FTDistribution1DGauss::evaluate( q );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else
            return this->IParameterized::areParametersChanged(  );
    }
    
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else
            this->IParameterized::clearParameterPool(  );
    }
    
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else
            return this->IParameterized::createParameterTree(  );
    }
    
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else
            this->IParameterized::printParameters(  );
    }
    
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< FTDistribution1DGauss_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else
            return this->IParameterized::setParameterValue( name, value );
    }
    
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else
            this->IParameterized::setParametersAreChanged(  );
    }
    
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_FTDistribution1DGauss_class(){

    { //::FTDistribution1DGauss
        typedef bp::class_< FTDistribution1DGauss_wrapper, bp::bases< IFTDistribution1D > > FTDistribution1DGauss_exposer_t;
        FTDistribution1DGauss_exposer_t FTDistribution1DGauss_exposer = FTDistribution1DGauss_exposer_t( "FTDistribution1DGauss", bp::init< double >(( bp::arg("omega") )) );
        bp::scope FTDistribution1DGauss_scope( FTDistribution1DGauss_exposer );
        { //::FTDistribution1DGauss::clone
        
            typedef ::FTDistribution1DGauss * ( ::FTDistribution1DGauss::*clone_function_type )(  ) const;
            typedef ::FTDistribution1DGauss * ( FTDistribution1DGauss_wrapper::*default_clone_function_type )(  ) const;
            
            FTDistribution1DGauss_exposer.def( 
                "clone"
                , clone_function_type(&::FTDistribution1DGauss::clone)
                , default_clone_function_type(&FTDistribution1DGauss_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FTDistribution1DGauss::evaluate
        
            typedef double ( ::FTDistribution1DGauss::*evaluate_function_type )( double ) const;
            typedef double ( FTDistribution1DGauss_wrapper::*default_evaluate_function_type )( double ) const;
            
            FTDistribution1DGauss_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::FTDistribution1DGauss::evaluate)
                , default_evaluate_function_type(&FTDistribution1DGauss_wrapper::default_evaluate)
                , ( bp::arg("q") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( FTDistribution1DGauss_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            FTDistribution1DGauss_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&FTDistribution1DGauss_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( FTDistribution1DGauss_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            FTDistribution1DGauss_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&FTDistribution1DGauss_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( FTDistribution1DGauss_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            FTDistribution1DGauss_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&FTDistribution1DGauss_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( FTDistribution1DGauss_wrapper::*default_printParameters_function_type )(  ) const;
            
            FTDistribution1DGauss_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&FTDistribution1DGauss_wrapper::default_printParameters) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            FTDistribution1DGauss_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &FTDistribution1DGauss_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( FTDistribution1DGauss_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            FTDistribution1DGauss_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&FTDistribution1DGauss_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( FTDistribution1DGauss_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            FTDistribution1DGauss_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&FTDistribution1DGauss_wrapper::default_setParametersAreChanged) );
        
        }
    }

}
