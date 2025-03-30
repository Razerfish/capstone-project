add_library(libvlcpp INTERFACE)
target_include_directories(libvlcpp INTERFACE ./libvlcpp)

target_link_libraries(libvlcpp INTERFACE -lvlc)
