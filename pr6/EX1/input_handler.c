
#include <stdio.h>
#include <string.h>

char* get_input(char* buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return NULL;
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}
