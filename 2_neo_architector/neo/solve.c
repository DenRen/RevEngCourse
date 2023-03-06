#include <stdlib.h>
#include <string.h>

char* whatisyourname() {
    const unsigned name_len = 256;

    char* name = malloc(name_len + 1);
    if (name == NULL) {
        return NULL;
    }

    memset(name, -1u, name_len);
    name[name_len] = 0;

    return name;
}
