#include "compiler.h"

#include <stdio.h>

int main(int argc, char** argv) {
    return tl_compiler_build("test", "stdlib/test.tl");
}