add_executable(TeglaClient)

if(CMAKE_SYSTEM_NAME STREQUAL "NetBSD")
    target_include_directories(TeglaClient
        PRIVATE
            /usr/X11R7/include
    )
    target_link_directories(TeglaClient
        PRIVATE
            /usr/X11R7/lib
    )
endif()

target_sources(TeglaClient
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(TeglaClient
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(TeglaClient
    PRIVATE
        TeglaCore
        Mw
        GL
)
