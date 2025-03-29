configure_file(AppInfo.h.in AppInfo.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARIES})

add_executable(main main.cpp)

target_link_libraries(main ${GTKMM_LIBRARIES})
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}/src")
