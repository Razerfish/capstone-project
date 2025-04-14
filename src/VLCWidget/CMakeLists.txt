include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_library(VLCWidget VLCWidget.cpp)

target_link_libraries(VLCWidget PUBLIC ${GTKMM_LIBRARIES} libvlcpp)
target_include_directories(VLCWidget INTERFACE .)
