# The minimum required version of CMake corresponds to the one in Ubuntu 14.04
# LTS
cmake_minimum_required(VERSION 3.1.0)

# CMake policies
cmake_policy(SET CMP0042 NEW)
cmake_policy(SET CMP0048 NEW)

# Using C++14
set(CMAKE_CXX_STANDARD 14)

# Version Information
set(POLYSHAPER_3DCAM_VER_MAJ 0)
set(POLYSHAPER_3DCAM_VER_MIN 1)
set(POLYSHAPER_3DCAM_VER_PAT 0)

message(STATUS "PolyShaper 3DCam version: ${POLYSHAPER_3DCAM_VER_MAJ}.${POLYSHAPER_3DCAM_VER_MIN}.${POLYSHAPER_3DCAM_VER_PAT}")

project(PolyShaper3Dcam VERSION ${POLYSHAPER_3DCAM_VER_MAJ}.${POLYSHAPER_3DCAM_VER_MIN}.${POLYSHAPER_3DCAM_VER_PAT} LANGUAGES CXX)
set(CMAKE_COLOR_MAKEFILE ON)

# Enabling test globally
enable_testing()

# Adding the current directory to the include path and instructing CMake to run
# moc automatically when needed (this is needed by QT)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# QT packages we use
find_package(Qt5Test REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)

# RPATH configuration. We always use RPATH (both when building and when
# installing). The following code snippet (with comments and minor changes) is
# taken from https://cmake.org/Wiki/CMake_RPATH_handling
# ==============================================================================
# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH OFF)
# when building, don't use the install RPATH already (but later on when
# installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH OFF)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# add the automatically determined parts of the RPATH which point to directories
# outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()
# enable the installation of RPATH
set(CMAKE_SKIP_INSTALL_RPATH OFF)
# ==============================================================================

# The variable containing the path relative to CMAKE_INSTALL_PREFIX for
# miscellaneous files
if(WIN32)
	set(MISC_FILES_DESTINATION .)
else()
	set(MISC_FILES_DESTINATION share/PolyShaper3Dcam)
endif()

# The position of the qrc file with QML scripts. This is compiled in the app
set(POLYSHAPER_3DCAM_QML_QRC "${CMAKE_SOURCE_DIR}/qml/qml.qrc")

# Adding all subdirectories
add_subdirectory(3dcamlib)
add_subdirectory(app)
add_subdirectory(test)

# Setting install destination for some files
install(FILES "LICENSE" DESTINATION "${MISC_FILES_DESTINATION}")
install(FILES "README.md" DESTINATION "${MISC_FILES_DESTINATION}")
