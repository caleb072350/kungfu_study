CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

PROJECT(longgist)

#######################################################

file (STRINGS config.in ConfigContents)
foreach(NameAndValue ${ConfigContents})
    string(REGEX REPLACE "^[ ]+" "" NameAndValue ${NameAndValue})
    string(REGEX MATCH "^[^=]+" Name ${NameAndValue})
    string(REPLACE "${Name}=" "" Value ${NameAndValue})
    set(${Name} "${Value}")
    MESSAGE( STATUS ${Name} " = " ${Value} )
endforeach()

#######################################################

INSTALL(DIRECTORY longfist DESTINATION "include")

INSTALL(DIRECTORY api/ctp/${CTP_VERSION}/include/ DESTINATION "include/ctp")
INSTALL(DIRECTORY api/ctp/${CTP_VERSION}/lib/ DESTINATION "lib64/api")

