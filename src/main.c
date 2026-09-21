#include <stdio.h>
#include "json_loader.h"

int main(int argc, char *argv[]){
    //No input file
    if(argc < 2){
        printf("Input file required. \n Argument count: %d\n", argc);
        return 1;
    }

    struct Server server;

    if(load_server_from_json(argv[1], &server) != 0){
        printf("Unable to load server. \n");
        return 1;
    }

    printf("Server name: %s\n", server.name);

    free_server(&server);

    return 0;
}

/*
argc - argument count
argv - argument vector
command line arguments retrieved when calling functions

e.g.
./discord-to-md server.json
argc = 2
argv[0] = "./discord-to-md"
argv[1] = "server.json"
*/