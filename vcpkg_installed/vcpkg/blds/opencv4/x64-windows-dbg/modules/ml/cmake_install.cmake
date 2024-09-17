# Install script for directory: C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/src/4.8.0-2bf495557d.clean/modules/ml

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/pkgs/opencv4_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/lib/opencv_ml4d.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libs" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/bin/opencv_ml4d.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "pdb")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/bin/opencv_ml4d.pdb")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2" TYPE FILE OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/src/4.8.0-2bf495557d.clean/modules/ml/include/opencv2/ml.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/ml" TYPE FILE OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/src/4.8.0-2bf495557d.clean/modules/ml/include/opencv2/ml/ml.hpp")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2/ml" TYPE FILE OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/src/4.8.0-2bf495557d.clean/modules/ml/include/opencv2/ml/ml.inl.hpp")
endif()

