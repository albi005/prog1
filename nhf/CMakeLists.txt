cmake_minimum_required(VERSION 3.0)
project(uwu)

# List all your source files explicitly
set(SOURCE_FILES
        main.c
        animal.c
        console.c
        draw.c
        econio.c
        input.c
        owner.c
        treatment.c
        utils.c
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -std=c11")

# Create the executable from the list of source files
add_executable(uwu ${SOURCE_FILES})
