add_executable(TeglaServer)

target_sources(TeglaServer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/NetworkServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Game/World.cpp
)

target_include_directories(TeglaServer
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/vendor/raknet/include
)

target_link_libraries(TeglaServer
    PRIVATE
        TeglaCore
        raknet
)