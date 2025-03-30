include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_library(BackgroundWindow BackgroundWindow.cpp)

target_link_libraries(BackgroundWindow PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(BackgroundWindow INTERFACE .)
