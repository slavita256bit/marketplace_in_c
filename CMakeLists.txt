cmake_minimum_required(VERSION 4.1)
project(marketplace_in_c C)

set(CMAKE_C_STANDARD 23)

include(CheckSymbolExists)

add_executable(marketplace_in_c main.c
        product.c
        product.h
        settings.h
        io.c
        io.h
        image.c
        image.h)

add_custom_target(run
        COMMAND konsole --hold -e $<TARGET_FILE:marketplace_in_c>
        DEPENDS marketplace_in_c
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

