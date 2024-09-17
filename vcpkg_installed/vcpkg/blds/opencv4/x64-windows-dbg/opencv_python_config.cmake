
set(CMAKE_BUILD_TYPE "Debug")

set(BUILD_SHARED_LIBS "ON")

set(CMAKE_C_FLAGS "  /nologo /DWIN32 /D_WINDOWS /W3 /utf-8 /MP   /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:precise /FS    ")

set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MDd /Z7 /Ob0 /Od /RTC1  ")

set(CMAKE_C_FLAGS_RELEASE "  /MD /O2 /Oi /Gy /DNDEBUG /Z7  ")

set(CMAKE_CXX_FLAGS "  /nologo /DWIN32 /D_WINDOWS /W4 /utf-8 /GR /MP   /D _CRT_SECURE_NO_DEPRECATE /D _CRT_NONSTDC_NO_DEPRECATE /D _SCL_SECURE_NO_WARNINGS /Gy /bigobj /Oi  /fp:precise /FS     /EHa /wd4127 /wd4251 /wd4324 /wd4275 /wd4512 /wd4589 /wd4819")

set(CMAKE_CXX_FLAGS_DEBUG " /D_DEBUG /MDd /Z7 /Ob0 /Od /RTC1  ")

set(CMAKE_CXX_FLAGS_RELEASE " /MD /O2 /Oi /Gy /DNDEBUG /Z7  ")

set(CV_GCC "")

set(CV_CLANG "")

set(ENABLE_NOISY_WARNINGS "OFF")

set(CMAKE_MODULE_LINKER_FLAGS "/machine:x64 ")

set(CMAKE_INSTALL_PREFIX "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/pkgs/opencv4_x64-windows/debug")

set(OPENCV_PYTHON_INSTALL_PATH "")

set(OpenCV_SOURCE_DIR "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/src/4.8.0-2bf495557d.clean")

set(OPENCV_FORCE_PYTHON_LIBS "")

set(OPENCV_PYTHON_SKIP_LINKER_EXCLUDE_LIBS "")

set(OPENCV_PYTHON_BINDINGS_DIR "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator")

set(cv2_custom_hdr "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_custom_headers.h")

set(cv2_generated_files "C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_enums.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_funcs.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_include.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_modules.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_modules_content.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_types.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_generated_types_content.h;C:/Users/tomer/source/repos/miniproj/vcpkg_installed/vcpkg/blds/opencv4/x64-windows-dbg/modules/python_bindings_generator/pyopencv_signatures.json")
