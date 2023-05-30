CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

PROJECT(wingchun)

SET(CTP_SOURCE_FILES MDEngineCTP.cpp MDEngineCTP.h IMDEngine.cpp IMDEngine.h ../base/IEngine.cpp ../base/IEngine.h)

ADD_LIBRARY(ctpmd SHARED ${CTP_SOURCE_FILES})
# TARGET_LINK_LIBRARIES(ctpmd journal kflog thostmduserapi ${Boost_LIBRARIES})

find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)
FIND_PACKAGE(Boost 1.82.0 COMPONENTS python)


TARGET_LINK_LIBRARIES(ctpmd journal kflog thostmduserapi Boost::python ${Boost_LIBRARIES})

INSTALL(TARGETS ctpmd DESTINATION "lib/wingchun")