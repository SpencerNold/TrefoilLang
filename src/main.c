#include "compiler.h"

#include <stdio.h>

int main(int argc, char** argv) {
    int code = tl_compiler_build("test", "stdlib/test.tl");
}