cmake_minimum_required(VERSION 3.29.3)

project(tlang VERSION 0.0.1 DESCRIPTION "TrefoilLang Compiler")

find_package(LLVM REQUIRED CONFIG)

set(SOURCES
    src/error.c
    src/compiler.c
    src/lexer.c
    src/parser.c
)

message(STATUS ${LLVM_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    ${SOURCES}
    src/main.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE include
    PUBLIC ${LLVM_INCLUDE_DIRS}
)

llvm_map_components_to_libnames(LLVM_LIBS core support irreader)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${LLVM_LIBS}
)