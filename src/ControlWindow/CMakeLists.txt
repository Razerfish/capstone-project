include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_library(ControlWindow ControlWindow.cpp)

target_link_libraries(ControlWindow PRIVATE ${GTKMM_LIBRARIES} Application)
target_include_directories(ControlWindow INTERFACE .)
