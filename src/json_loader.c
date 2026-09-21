#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "json_loader.h"

static int parse_server(cJSON *json, struct Server *server){
    
}

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
    cJSON *categories = cJSON_GetObjectItem(json, "categories");
    
    if (categories != NULL && cJSON_IsArray(categories)) {
        server->category_count = cJSON_GetArraySize(categories);

        server->categories = malloc(
            server->category_count * sizeof(struct Category)
        );

        if (server->categories == NULL) {
            free(server->name);
            cJSON_Delete(json);
            return 1;
        }
        //for each category
        for (size_t i = 0; i < server->category_count; i++) {
            cJSON *category = cJSON_GetArrayItem(categories, i);

            if (category == NULL || !cJSON_IsObject(category)) {
                free_server(server);
                cJSON_Delete(json);
                return 1;
            }


            // Load single category name
            cJSON *category_name =
                cJSON_GetObjectItem(category, "name");

            if (category_name == NULL || !cJSON_IsString(category_name)) {
                free_server(server);
                cJSON_Delete(json);
                return 1;
            }

            server->categories[i].name =
                malloc(strlen(category_name->valuestring) + 1);

            if (server->categories[i].name == NULL) {
                free_server(server);
                cJSON_Delete(json);
                return 1;
            }

            strcpy(
                server->categories[i].name,
                category_name->valuestring
            );
            // --------------------------------------------------------

            // Load channels
            cJSON *channels = cJSON_GetObjectItem(category, "channels");

            if (channels != NULL && cJSON_IsArray(channels)) {

                server->categories[i].channel_count =
                    cJSON_GetArraySize(channels);

                server->categories[i].channels =
                    malloc(
                        server->categories[i].channel_count
                        * sizeof(struct Channel)
                    );

                if (server->categories[i].channels == NULL) {
                    free_server(server);
                    cJSON_Delete(json);
                    return 1;
                }
            }
            //for each channel
            for (size_t j = 0;
                j < server->categories[i].channel_count;
                j++) {

                cJSON *channel = cJSON_GetArrayItem(channels, j);

                if (channel == NULL || !cJSON_IsString(channel)) {
                    free_server(server);
                    cJSON_Delete(json);
                    return 1;
                }
                //load channel name
                server->categories[i].channels[j].name = malloc(strlen(channel->valuestring) + 1);

                if (server->categories[i].channels[j].name == NULL) {
                    free_server(server);
                    cJSON_Delete(json);
                    return 1;
                }

                strcpy(
                    server->categories[i].channels[j].name,
                    channel->valuestring
                );
            }
        }
    }
    return 0;
}


// ============================================================
// Free Server
// ============================================================

void free_server(struct Server *server)
{
    //free server
    free(server->name);

    //free categories
    for (size_t i = 0; i < server->category_count; i++) {
        //free category
        free(server->categories[i].name);

        //free channels
        for (size_t j = 0;
             j < server->categories[i].channel_count;
             j++) {

            free(server->categories[i].channels[j].name);
        }

        free(server->categories[i].channels);
    }

    free(server->categories);
}