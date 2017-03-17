# Script to compile the PolyShaper 3D Cam library

# We need CGAL
find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

find_package(Boost REQUIRED)

set(POLYSHAPER_3DCAM_LIB_SRCS
        gcodegenerator.cpp
        stlloader.cpp)
set(POLYSHAPER_3DCAM_LIB_HDRS
        gcodegenerator.h
        stlloader.h)

add_library(3dcamlib STATIC ${POLYSHAPER_3DCAM_LIB_SRCS} ${POLYSHAPER_3DCAM_LIB_HDRS})

# Specifying the the include directories: they are used both here and exported
# by this library (so that targets linking this one will automatically import
# the include directories declared here)
target_include_directories(3dcamlib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CGAL_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIRS}>)

# Adding dependencies (they are also exported)
target_link_libraries(3dcamlib Qt5::Core Qt5::Concurrent Qt5::QuickControls2 ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

# Specifying the public headers of this target
set_property(TARGET 3dcamlib PROPERTY PUBLIC_HEADER ${POLYSHAPER_3DCAM_LIB_HDRS})
