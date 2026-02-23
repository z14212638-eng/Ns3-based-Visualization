# Install script for directory: /home/zk/algorithm/ns-3.46/ns-3.46/src/stats

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "default")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so"
         RPATH "/usr/local/lib:\$ORIGIN/:\$ORIGIN/../lib:/usr/local/lib64:\$ORIGIN/:\$ORIGIN/../lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/zk/algorithm/ns-3.46/ns-3.46/build/lib/libns3.46-stats-default.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so"
         OLD_RPATH "/home/zk/algorithm/ns-3.46/ns-3.46/build/lib:::::::::::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib:\$ORIGIN/:\$ORIGIN/../lib:/usr/local/lib64:\$ORIGIN/:\$ORIGIN/../lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libns3.46-stats-default.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/sqlite-output.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ns3" TYPE FILE FILES
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/sqlite-data-output.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/helper/file-helper.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/helper/gnuplot-helper.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/average.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/basic-data-calculators.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/boolean-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/data-calculator.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/data-collection-object.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/data-collector.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/data-output-interface.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/double-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/file-aggregator.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/get-wildcard-matches.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/gnuplot-aggregator.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/gnuplot.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/histogram.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/omnet-data-output.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/stats.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/time-data-calculators.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/time-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/time-series-adaptor.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/uinteger-16-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/uinteger-32-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/src/stats/model/uinteger-8-probe.h"
    "/home/zk/algorithm/ns-3.46/ns-3.46/build/include/ns3/stats-module.h"
    )
endif()

