#include "compiler.h"

#include "error.h"
#include "lexer.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tl_compiler_build(char* out, char* in) {
    FILE* file = fopen(in, "r");
    if (file == NULL) {
        return -1;
    }
    const int size = 4096;
    char buf[size];
    int count = 0;
    while (fgets(buf, size, file)) {
        count++;
        int i;
        for (i = 0; i < size; i++)
            if (buf[i] == '\n') break;
        if (i == size) return -2;
        char* line = (char*) buf;
        int offset = 0;
        while (offset < strlen(line)) {
            TL_LexOut out = tl_lexer_read_token(line, offset, strlen(line) - offset);
            if (out.type == 0) {
                tl_error("syntax error", in, count, line);
                return -3;
            }
            if (out.type != NOP) {
                int length = out.offset - out.start;
                char buffer[255] = {0};
                strncpy(buffer, line + out.start, length);
                printf("%d := %s\n", out.type, buffer);
            }
            offset = out.offset;
        }
    }
    fclose(file);
    return 0;
}