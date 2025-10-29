message("Configuring vendor dependencies...")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/milsko/CMakeLists.txt")
    add_subdirectory(milsko)
else()
    message(FATAL_ERROR "Milsko has not been found in vendor/. Please make sure all submodules have been cloned.")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/TeglaMixer/CMakeLists.txt")
    add_subdirectory(TeglaMixer)
else()
    message(FATAL_ERROR "Mixer has not been found in vendor/. Please make sure all submodules have been cloned.")
endif()


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/raknet/CMakeLists.txt")
    add_subdirectory(raknet)
else()
    message(FATAL_ERROR "RakNet has not been found in vendor/. Please make sure all submodules have been cloned.")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/quickjs-ng/CMakeLists.txt")
    add_subdirectory(quickjs-ng)
else()
    message(FATAL_ERROR "QuickJS-NG has not been found in vendor/. Please make sure all submodules have been cloned.")
endif()