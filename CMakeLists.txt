cmake_minimum_required(VERSION 4.1)
project(marketplace_in_c C)

set(CMAKE_C_STANDARD 23)

add_executable(marketplace_in_c main.c
        product.c
        product.h
        settings.h
        io.c
        io.h
        stack.c
        stack.h
        image.c
        image.h
        tree.c
        tree.h
        interaction.c
        interaction.h
        utils.h)

if(WIN32)
    target_compile_definitions(marketplace_in_c PRIVATE USE_CONIO)
endif()

if(UNIX)
    target_sources(marketplace_in_c PRIVATE linux-specific/conio.c linux-specific/conio.h)
    target_include_directories(marketplace_in_c PRIVATE linux-specific)
endif()

add_custom_target(run
        COMMAND konsole --hold -e $<TARGET_FILE:marketplace_in_c>
        DEPENDS marketplace_in_c
        WORKING_DIRECTORY /home/slavita/CLionProjects/marketplace_in_c
)

