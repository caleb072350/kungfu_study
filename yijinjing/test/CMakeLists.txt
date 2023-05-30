project(Boost_test)

cmake_minimum_required(VERSION 2.8.3)

#find python
find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)

list(
    APPEND _components
    python${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}
    python${PYTHON_VERSION_MAJOR}
    python
)

message(BOOST_ROOT " ${BOOST_ROOT}")

set(_boost_python_found "")
set(Boost_NAMESPACE "libboost")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
foreach(_component IN ITEMS ${_components})
    find_package(Boost COMPONENTS ${_component})
    if(Boost_FOUND)
        set(_boost_python_found ${_component})
        break()
    endif()
    
endforeach()

include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})

message(PYTHON_INCLUDE_DIRS " ${PYTHON_INCLUDE_DIRS}")
message(PYTHON_LIBRARIES " ${PYTHON_LIBRARIES}")
message(Boost_INCLUDE_DIRS " ${Boost_INCLUDE_DIR}")
message(Boost_LIBRARIES " ${Boost_LIBRARIES}")

ADD_SUBDIRECTORY(HelloWorld)
