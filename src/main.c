#include <stdio.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Input file required. \n Argument count: %d\n", argc);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(file == NULL){
        printf("File inaccessibe or null.");
        return 1;
    }
    fclose(file);

    printf("Succesfully opened file.");

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