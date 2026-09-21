#include <stdio.h>

int main(int argc, char *argv[]){
    printf("Arguments: %d\n", argc);

    for(int i=0; i < argc; i++){
        printf("Argument %d: %s\n", i, argv[i]);
    }

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