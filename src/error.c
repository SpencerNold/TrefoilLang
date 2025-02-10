#include "error.h"

#include <stdio.h>

void tl_error(char* msg, char* file, int index, char* line) {
    printf("\n%s in %s on line %d\n", msg, file, index);
    printf("--->    %s\n", line);
}