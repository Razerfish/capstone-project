include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_library(Application Application.cpp)

target_link_libraries(Application PRIVATE ${GTKMM_LIBRARIES} BackgroundWindow VLCWidget ControlWindow)
target_include_directories(Application INTERFACE .)
