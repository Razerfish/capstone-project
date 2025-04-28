configure_file(AppInfo.h.in AppInfo.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_subdirectory(BackgroundWindow)
add_subdirectory(VLCWidget)
add_subdirectory(Application)
add_subdirectory(ControlWindow)

add_executable(main main.cpp)

# TODO: Remove Background window from target_link_libraries
target_link_libraries(main PUBLIC BackgroundWindow Application)
target_include_directories(main PUBLIC
    "${PROJECT_BINARY_DIR}/src"
)
