cmake_minimum_required(VERSION 3.8)

project(reverse_shell C)

set(CMAKE_C_STANDARD 99)

add_executable(reverse_shell
        port_listener/reverseShell.c
)

add_executable(listener
        port_listener/listener.c
)

add_custom_target(run_reverse
        COMMAND ./reverse_shell 127.0.0.1 4444
        DEPENDS reverse_shell
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(run_listener
        COMMAND ./listener 127.0.0.1 1 65335
        DEPENDS listener
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)