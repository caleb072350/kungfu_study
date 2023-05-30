CMAKE_MINIMUM_REQUIRED(VERSION 3.7)
PROJECT(wingchun)

##############################################################

INCLUDE_DIRECTORIES(../longfist)
INCLUDE_DIRECTORIES(../longfist/api/ctp/v6.3.6_20160606/include)

INCLUDE_DIRECTORIES(../yijinjing/journal)
INCLUDE_DIRECTORIES(../yijinjing/log)
INCLUDE_DIRECTORIES(../yijinjing/paged)
INCLUDE_DIRECTORIES(../yijinjing/utils)

INCLUDE_DIRECTORIES(base)

LINK_DIRECTORIES(../yijinjing)

ADD_SUBDIRECTORY(md)
ADD_SUBDIRECTORY(td)