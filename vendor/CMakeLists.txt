message("Configuring vendor dependencies...")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/milsko/CMakeLists.txt")
    add_subdirectory(milsko)
else()
    message(FATAL_ERROR "Milsko has not been found in vendor/. Please make sure all submodules have been cloned.")
endif()
