
# Our Project

cmake_minimum_required(VERSION 3.27)
project(psw_generator C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        main.c
        generate.c
        generate.h
        evaluatepsw.c
        evaluatepsw.h
        main.h
        pswFileIO.c
        pswFileIO.h
)

add_executable(psw_generator ${SOURCE_FILES} )
