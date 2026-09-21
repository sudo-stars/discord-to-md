#ifndef JSON_LOADER_H
#define JSON_LOADER_H
#include <stddef.h>

struct Category {
    char *name;
};

struct Server {
    char *name;

    struct Category *categories;
    size_t category_count;
};

int load_server_from_json(const char *filename, struct Server *server);

void free_server(struct Server *server);

#endif

// see  C include guards