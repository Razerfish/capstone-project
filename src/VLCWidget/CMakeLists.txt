include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_library(VLCWidget VLCWidget.cpp)

target_link_libraries(VLCWidget PRIVATE ${GTKMM_LIBRARIES} -lvlc)

target_include_directories(VLCWidget INTERFACE .)
