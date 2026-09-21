#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "json_loader.h"


int load_server_from_json(const char *filename, struct Server *server)
{
    // Access input file
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
    // --------------------------------------------------------


    // Parse JSON
    cJSON *json = cJSON_Parse(buffer);

    if (json == NULL) {
        return 1;
    }
    // --------------------------------------------------------

    
    // Load server name
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
    // --------------------------------------------------------


    // Load categories
    cJSON *category = cJSON_GetObjectItem(json, "category");

    if (category != NULL && cJSON_IsString(category)) {

        server->categories = malloc(sizeof(struct Category));

        if (server->categories == NULL) {
            free(server->name);
            cJSON_Delete(json);
            return 1;
        }

        server->category_count = 1;

        server->categories[0].name =
            malloc(strlen(category->valuestring) + 1);

        if (server->categories[0].name == NULL) {
            free(server->categories);
            free(server->name);
            cJSON_Delete(json);
            return 1;
        }

        strcpy(
            server->categories[0].name,
            category->valuestring
        );
    }
    // --------------------------------------------------------


    // Finished loading server
    return 0;
}


void free_server(struct Server *server)
{
    // Free server name
    free(server->name);
    // --------------------------------------------------------


    // Free categories
    for (size_t i = 0; i < server->category_count; i++) {
        free(server->categories[i].name);
    }
    free(server->categories);
    // --------------------------------------------------------
}