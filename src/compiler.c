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
        size_t i;
        for (i = 0; i < size; i++)
            if (buf[i] == '\n') break;
        if (i == size) return -2;
        char* line = (char*) buf;
        i = strlen(line);
        if (line[i - 1] != '\n') {
            // ensure all lines end with \n
            line[i] = '\n';
            line[++i] = 0;
        }
        int offset = 0;
        while (offset < i) {
            TL_LexOut out = tl_lexer_read_token(line, offset, strlen(line) - offset);
            if (out.type == 0) {
                tl_error("syntax error", in, count, line);
                return -3;
            }
            if (out.type != NOP) {
                int length = out.offset - out.start;
                char* buffer = (char*) malloc(length);
                strncpy(buffer, line + out.start, length);
                buffer[length] = 0;
                printf("%d := %s\n", out.type, buffer);
                free(buffer); // TODO remove when I actually do something with buffer
            }
            offset = out.offset;
        }
    }
    fclose(file);
    return 0;
}