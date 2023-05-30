CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(yijinjing)

#######################################################################

INCLUDE_DIRECTORIES(../longfist)
INCLUDE_DIRECTORIES(../longfist/api/ctp/v6.3.6_20160606/include)

INCLUDE_DIRECTORIES(journal)
INCLUDE_DIRECTORIES(log)
INCLUDE_DIRECTORIES(paged)
INCLUDE_DIRECTORIES(utils)

ADD_SUBDIRECTORY(journal)
ADD_SUBDIRECTORY(log)
ADD_SUBDIRECTORY(paged)
ADD_SUBDIRECTORY(test)