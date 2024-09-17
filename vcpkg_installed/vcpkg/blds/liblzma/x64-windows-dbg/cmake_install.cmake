# Install script for directory: C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/pkgs/liblzma_x64-windows/debug")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/lzma.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Runtime" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/liblzma.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/src/liblzma/api/" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma/liblzma-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma/liblzma-targets.cmake"
         "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/CMakeFiles/Export/6194817f435e7429e84a3ab7f926109c/liblzma-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma/liblzma-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma/liblzma-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma" TYPE FILE FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/CMakeFiles/Export/6194817f435e7429e84a3ab7f926109c/liblzma-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma" TYPE FILE FILES "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/CMakeFiles/Export/6194817f435e7429e84a3ab7f926109c/liblzma-targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/liblzma" TYPE FILE FILES
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/liblzma-config.cmake"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/liblzma-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "liblzma_Documentation" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/xz" TYPE DIRECTORY OPTIONAL FILES
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/api"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/examples"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Documentation" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/xz" TYPE FILE FILES
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/AUTHORS"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/COPYING"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/COPYING.0BSD"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/COPYING.GPLv2"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/NEWS"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/README"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/THANKS"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/faq.txt"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/history.txt"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/lzma-file-format.txt"
    "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/src/v5.6.0-0bc01dfc88.clean/doc/xz-file-format.txt"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/liblzma/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
