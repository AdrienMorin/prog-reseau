cmake_minimum_required(VERSION 3.26)
project(prog_reseau C)

set(CMAKE_C_STANDARD 11)

add_executable(prog_reseau
        socket_client.c
        socket_server.c)
