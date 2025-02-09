#include "lexer.h"

#include <stdio.h>
#include <string.h>

int main() {
    char* line = "+= -= *= /= %= ** ++ -- < > <= >= && || ! ? & | ^ ~ << >>\n";

    int offset = 0;
    while (offset < strlen(line)) {
        TL_LexOut out = tl_lexer_read_token(line, offset, strlen(line) - offset);

        if (out.type == 0) {
            printf("\nsyntax error on line: %d\n", 1);
            printf("--->    %s\n", line);
            return 1;
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