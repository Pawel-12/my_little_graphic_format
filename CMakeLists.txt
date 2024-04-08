cmake_minimum_required(VERSION 3.27)
project(my_little_graphic_format)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -static-libstdc++ -static-libgcc")

if (${WIN32})

    set(SDL2_INCLUDE_DIR C:/SDL2_64/include)
    set(SDL2_LIB_DIR C:/SDL2_64/lib)

    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})

endif ()

file(
        GLOB SOURCES LIST_DIRECTORIES false
        ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp
)

add_executable(my_little_graphic_format ${SOURCES})

set_target_properties(my_little_graphic_format PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin")

if (${WIN32})
    target_link_libraries(my_little_graphic_format mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
else()
    target_link_libraries(my_little_graphic_format SDL2main SDL2 SDL2_image SDL2_ttf)
endif ()