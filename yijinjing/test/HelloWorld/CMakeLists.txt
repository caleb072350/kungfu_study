set(MODULE_NAME hello)

include_directories(${CMAKE_SOURCE_DIR})

add_library(${MODULE_NAME} SHARED HelloWorld.cpp)

if (UNIX)
    set_target_properties(${MODULE_NAME} PROPERTIES PREFIX "")
elseif (WIN32)
    set_target_properties(${MODULE_NAME} PROPERTIES SUFFIX ".pyd")
endif()

target_link_libraries(${MODULE_NAME} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})