add_library(TeglaCore)

target_sources(TeglaCore
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
)

target_include_directories(TeglaCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)