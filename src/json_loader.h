#ifndef JSON_LOADER_H
#define JSON_LOADER_H

struct Server {
    char *name;
};

int load_server_from_json(const char *filename, struct Server *server);

void free_server(struct Server *server);

#endif

// see  C include guards