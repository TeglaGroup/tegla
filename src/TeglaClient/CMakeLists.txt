add_executable(TeglaClient)

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