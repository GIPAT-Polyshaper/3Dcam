# Script to compile the PolyShaper 3D Cam application

set(POLYSHAPER_3DCAM_APP_SRCS
	main.cpp)

# Adding the qrc with qml scripts
qt5_add_resources(POLYSHAPER_3DCAM_APP_SRCS ${POLYSHAPER_3DCAM_QML_QRC})

add_executable(3dcam ${POLYSHAPER_3DCAM_APP_SRCS})

# Adding dependencies (they are also exported, so targets linking this one will
# automatically link libraries declared here)
target_link_libraries(3dcam 3dcamlib Qt5::Core Qt5::Concurrent Qt5::QuickControls2)

# Installation paths
install(TARGETS 3dcam
	RUNTIME DESTINATION bin/)
