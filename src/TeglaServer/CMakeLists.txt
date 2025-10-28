add_executable(TeglaServer)

target_sources(TeglaServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(TeglaServer
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(TeglaServer
    PRIVATE
        TeglaCore
)