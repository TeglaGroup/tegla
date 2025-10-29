add_library(TeglaCore STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ScriptingCore.cpp
)

target_include_directories(TeglaCore
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/vendor/quickjs-ng
)

target_link_libraries(TeglaCore
    PRIVATE
        qjs
)