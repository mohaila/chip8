set(TARGET Manager)
set(SRC sdlmanager.cpp)

add_library(${TARGET} SHARED ${SRC})
target_include_directories(${TARGET} PRIVATE 
    ${CMAKE_SOURCE_DIR}/source
)
target_link_libraries(${TARGET} PRIVATE
    SDL2
)

target_precompile_headers(${TARGET} PRIVATE pch.h)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${TARGET} PROPERTIES LINK_FLAGS_RELEASE -s) 
endif()

if(ENABLE_COVERAGE)
    target_compile_options(${TARGET} PRIVATE -O0 -coverage -fno-exceptions -fno-inline)
    target_link_options(${TARGET} PRIVATE -coverage)
endif()