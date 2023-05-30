CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(journal)

IF(USE_SERVICE)
    ADD_DEFINITIONS(-DUSE_PAGED_SERVICE)
ENDIF(USE_SERVICE)

IF(USE_HASH_CODE)
    ADD_DEFINITIONS(-DFRAME_AUTO_SET_HASHCODE)
ENDIF(USE_HASH_CODE)

SET(LIB_UTIL_INCLUDE_FILES ../utils/Timer.h ../utils/Hash.hpp ../utils/TypeConvert.hpp
        ../utils/json.hpp ../utils/PosHandler.hpp)

SET(LIB_UTIL_SOURCE_FILES ../utils/Timer.cpp)

SET(LIB_INCLUDE_FILES ../utils/constants.h ../utils/YJJ_DECLARE.h Frame.hpp FrameHeader.h Journal.h JournalHandler.h 
        JournalReader.h JournalWriter.h Page.h PageUtil.h PageHeader.h PageProvider.h IPageProvider.h 
        StrategySocketHandler.h StrategyUtil.h IJournalVisitor.h IStrategyUtil.h)
    
SET(LIB_SOURCE_FILES Journal.cpp JournalHandler.cpp JournalReader.cpp JournalWriter.cpp Page.cpp PageUtil.cpp 
        PythonExtend.cpp PageProvider.cpp StrategyUtil.cpp)
    
ADD_LIBRARY(${PROJECT_NAME} SHARED ${LIB_SOURCE_FILES} ${LIB_INCLUDE_FILES} ${LIB_UTIL_SOURCE_FILES} ${LIB_UTIL_INCLUDE_FILES})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES SOVERSION 1.1 VERSION 1.1)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

MESSAGE(STATUS CMAKE_Boost_LIBRARIES " ${Boost_LIBRARIES}")

# find_package
find_package(PythonInterp REQUIRED)
find_package(PythonLibs ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} EXACT REQUIRED)


TARGET_LINK_LIBRARIES(${PROJECT_NAME} Boost::python ${Boost_LIBRARIES})

INSTALL(FILES ${LIB_UTIL_INCLUDE_FILES} ${LIB_INCLUDE_FILES} DESTINATION "include")

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION "lib/yijinjing")