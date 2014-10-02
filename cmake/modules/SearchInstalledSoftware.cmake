# Search for installed software required by BornAgain



if(BORNAGAIN_OPENMPI)
    message(STATUS "Configuring with OpenMPI support")
    find_package(MPI REQUIRED)
endif()


# --- Eigen3 ---
find_package(Eigen3 3.1.0)
if(NOT EIGEN3_FOUND) 
    set(EIGEN3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/ThirdParty/eigen3)
    message(STATUS "--> Build in version of Eigen3 will be used")
endif()

# --- FFTW3 ---
find_package(FFTW REQUIRED)

# --- BOOST ---
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON) 
set(Boost_USE_STATIC_RUNTIME OFF)
add_definitions(-DBOOST_ALL_DYN_LINK) # line is needed for MSVC
#add_definitions(-DBOOST_LIB_DIAGNOSTIC) # shows during compilation auto-linked libraries
if(WIN32)
    set(boost_libraries_required date_time chrono program_options zlib bzip2 iostreams system filesystem regex thread)
else()
    set(boost_libraries_required date_time chrono program_options iostreams system filesystem regex thread)
endif()
if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)
    list(APPEND boost_libraries_required python)
endif()
find_package(Boost 1.48.0 COMPONENTS ${boost_libraries_required} REQUIRED)
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

# --- GSL ---
find_package(GSL REQUIRED)

#if(NOT BUILTIN_GSL)
#    find_package(GSL REQUIRED)
#    if(GSL_FOUND)
#        include_directories(${GSL_INCLUDE_DIR})
#    else()
#        message(STATUS "No GSL has been found. Install it, or run cmake -DBUILTIN_GSL=ON to use build in GSL installation.")
#    endif()
#endif()

#if(BUILTIN_GSL)
#    set(gsl_version 1.9)
#    include(ExternalProject)
#    message(STATUS "Downloading and building GSL version ${gsl_version}")
#    ExternalProject_Add(
#      GSL
#      URL http://mirror.switch.ch/ftp/mirror/gnu/gsl/gsl-${gsl_version}.tar.gz
#      INSTALL_DIR ${CMAKE_BINARY_DIR}
#      CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix <INSTALL_DIR> --disable-shared
#    )
#    set(GSL_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/include)
#    set(GSL_LIBRARIES -L${CMAKE_BINARY_DIR}/lib -lgsl -lgslcblas -lm)
#endif()


# --- Python ---
if(BORNAGAIN_PYTHON OR BORNAGAIN_GUI)

    find_package(PythonInterp 2.7 REQUIRED)
    message(STATUS "--> PYTHON_VERSION_STRING: ${PYTHON_VERSION_STRING}, PYTHON_EXECUTABLE:${PYTHON_EXECUTABLE}")

    find_package(PythonLibs 2.7)
    message(STATUS "--> PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}, PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS} PYTHONLIBS_VERSION_STRING:${PYTHONLIBS_VERSION_STRING}")

    ValidatePythonIntstallation()

#    if(NOT PYTHONLIBS_FOUND)
#        message(STATUS "--> First attempt to find Python libraries failed, trying another way")
#        find_package(PythonLibsNew)
#    endif()

    if(NOT PYTHONLIBS_FOUND)
        message(FATAL_ERROR "No Python library has been found")
    endif()


#    set(AAA "aaa;bbb")
#    set(BBB "bbb")
#    if(NOT "${AAA}" STREQUAL "${BBB}")
#        message("AAA not equal")
#    else()
#        message("AAA equal")
#    endif()


#    if(WIN32)
#        find_package(PythonLibs REQUIRED)
#    else()
#       find_package(PythonLibsNew REQUIRED)
#    endif()

#    message(STATUS "--> PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}, PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS}")

    # TODO refactor this
#    if(APPLE)
#        find_package(PythonLibsNew REQUIRED)
#    elseif(WIN32)
#        find_package(PythonLibs REQUIRED)
#    else()
#        message("XXX ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}")
#        #set(PythonLibs_FIND_VERSION ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR})
#        find_package(PythonLibs REQUIRED)
#    endif()

#    # important to find interpreter and libraries from same python version
#    #if(NOT PYTHONLIBS_FOUND)
#    #    set(PythonLibs_FIND_VERSION ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}.${PYTHON_VERSION_PATCH})
#    #    find_package(PythonLibs REQUIRED)
#    #endif()
#    #if(NOT PYTHONLIBS_FOUND)
#    #    message(SEND_ERROR "No python libraries have been found")
#    #endif()


#    message(STATUS "--> PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}, PYTHON_INCLUDE_DIRS:${PYTHON_INCLUDE_DIRS}, PYTHONLIBS_VERSION_STRING:${PYTHONLIBS_VERSION_STRING}")
#    if(NOT PYTHONLIBS_FOUND)
#        message(FATAL_ERROR "No python libraries have been found")
#    endif()

#    if(NOT ${PYTHON_VERSION_STRING} STREQUAL ${PYTHONLIBS_VERSION_STRING})
#        message(WARNING "Seems that Python interpreter version ${PYTHON_VERSION_STRING} doesn't match version of Python library ${PYTHONLIBS_VERSION_STRING}")
#    endif()

    if(NOT WIN32)
        GET_FILENAME_COMPONENT(PyLibExtension ${PYTHON_LIBRARIES} EXT)
        if(${PyLibExtension}  STREQUAL ".a")
            find_package( Threads )
            set(syslibs "-lm -ldl -lutil ${CMAKE_THREAD_LIBS_INIT} -rdynamic")
            message(STATUS "--> Static python library detected, adding ${syslibs}")
            set(PYTHON_LIBRARIES "${syslibs} ${PYTHON_LIBRARIES}")
        endif()
    endif()
        
    find_package(Numpy REQUIRED)
endif()


# --- ROOT ---
if(ROOT_SUPPORT)
    find_package(ROOT)
endif()
