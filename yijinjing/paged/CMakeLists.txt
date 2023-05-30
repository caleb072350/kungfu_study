CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(paged)

SET(LIB_SOURCE_FILES PageEngine.h PageEngine.cpp PageSocketStruct.h PageSocketHandler.h PageSocketHandler.cpp PageServiceTask.h PageServiceTask.cpp PageCommStruct.h)
SET(LIB_FILES ${LIB_SOURCE_FILES})
ADD_LIBRARY(${PROJECT_NAME} ${LIB_FILES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} journal kflog)

INSTALL(FILES PageCommStruct.h PageSocketStruct.h DESTINATION "include")
INSTALL(TARGETS ${PROJECT_NAME} DESTINATION "lib/yijinjing")
