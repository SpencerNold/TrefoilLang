cmake_minimum_required(VERSION 3.29.3)

project(tlang VERSION 0.0.1 DESCRIPTION "TrefoilLang Compiler")

set(SOURCES
    src/lexer.c
    src/parser.c
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    src/main.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include
)