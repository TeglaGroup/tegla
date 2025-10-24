cmake_minimum_required(VERSION 3.0.0)
project(tegla)

# Use ANSI C
set(CMAKE_C_STANDARD 90)

# Version Information
set(TEGLA_VERSION_MAJOR 0)
set(TEGLA_VERSION_MINOR 0)
set(TEGLA_VERSION_PATCH 0)

# Options
option(USE_GTK2 "Use GTK2 instead of GTK3" OFF)

# PkgConfig
find_package(PkgConfig REQUIRED)

# Client
if(USE_GTK2)
	find_package(GTK2 REQUIRED)
	pkg_check_modules(GTKGLEXT REQUIRED IMPORTED_TARGET gtkglext-1.0 epoxy)
else()
	pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0>=3.16 epoxy)
endif()


file(GLOB tegla_client_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(tegla_client ${tegla_client_SRC})

if(USE_GTK2)
	target_link_libraries(tegla_client PRIVATE GTK2::gtk PkgConfig::GTKGLEXT)
else()
	target_link_libraries(tegla_client PRIVATE PkgConfig::GTK3)
endif()

find_library(MATH_LIB m)
if(MATH_LIB)
    target_link_libraries(tegla_client PRIVATE ${MATH_LIB})
endif()

message(STATUS "")
message(STATUS "Tegla Configuation:")
if(USE_GTK2)
	message(STATUS "GUI: Gtk+ 2.0/GtkGLExt")
else()
	message(STATUS "GUI: Gtk+ 3.0")
endif()
message(STATUS "")
