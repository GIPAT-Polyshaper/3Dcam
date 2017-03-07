# Script to compile the PolyShaper 3D Cam library

# We need CGAL
find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

set(POLYSHAPER_3DCAM_LIB_SRCS
	gcodegenerator.cpp)
set(POLYSHAPER_3DCAM_LIB_HDRS
	gcodegenerator.h)

message("${CGAL_LIBRARIES}")
message("${CGAL_HEADERS}")

add_library(3dcamlib STATIC ${POLYSHAPER_3DCAM_LIB_SRCS} ${POLYSHAPER_3DCAM_LIB_HDRS})

# Specifying the the include directories: they are used both here and exported
# by this library (so that targets linking this one will automatically import
# the include directories declared here)
target_include_directories(3dcamlib PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

# Adding dependencies (they are also exported)
target_link_libraries(3dcamlib Qt5::Core Qt5::Concurrent Qt5::QuickControls2 ${CGAL_LIBRARIES} ${CGAL_3RD_PARTY_LIBRARIES})

# Specifying the public headers of this target
set_property(TARGET 3dcamlib PROPERTY PUBLIC_HEADER ${SALSAUTILITIES_HDRS})
