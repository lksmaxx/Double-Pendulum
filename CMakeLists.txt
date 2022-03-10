cmake_minimum_required(VERSION 3.16)

project(DP_proj)

add_executable(DPend main.cpp)

add_subdirectory(src)

target_include_directories(DPend PUBLIC src)

target_link_directories(DPend PUBLIC lib)

target_link_libraries(DPend PUBLIC X11 ${CMAKE_SOURCE_DIR}/lib/libglfw3.a GL Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor) 

target_compile_options(DPend PUBLIC -g)

target_compile_definitions(DPend PUBLIC DEBUG)

install(TARGETS DPend DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
