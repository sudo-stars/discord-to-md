#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "json_loader.h"

int load_server_from_json(const char *filename, struct Server *server)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 1;
    }

    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return 1;
    }

    fclose(file);

    cJSON *json = cJSON_Parse(buffer);

    if (json == NULL) {
        return 1;
    }

    cJSON *name = cJSON_GetObjectItem(json, "name");

    if (name == NULL || !cJSON_IsString(name)) {
        cJSON_Delete(json);
        return 1;
    }

    server->name = malloc(strlen(name->valuestring) + 1);

    if (server->name == NULL) {
        cJSON_Delete(json);
        return 1;
    }

    strcpy(server->name, name->valuestring);

    cJSON_Delete(json);

    return 0;
}

void free_server(struct Server *server){
    free(server->name);
}