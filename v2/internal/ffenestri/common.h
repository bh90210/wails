//
// Created by Lea Anthony on 6/1/21.
//

#ifndef COMMON_H
#define COMMON_H

#include "hashmap.h"
#include "vec.h"

// Credit: https://stackoverflow.com/a/8465083
char* concat(const char *string1, const char *string2)
{
    const size_t len1 = strlen(string1);
    const size_t len2 = strlen(string2);
    char *result = malloc(len1 + len2 + 1);
    strcpy(result, string1);
    memcpy(result + len1, string2, len2 + 1);
    return result;
}


// 10k is more than enough for a log message
#define MAXMESSAGE 1024*10
char logbuffer[MAXMESSAGE];

void ABORT(const char *message, ...) {
    const char *temp = concat("FATAL: ", message);
    va_list args;
    va_start(args, message);
    vsnprintf(logbuffer, MAXMESSAGE, temp, args);
    printf("%s\n", &logbuffer[0]);
    MEMFREE(temp);
    va_end(args);
    exit(1);
}

int freeHashmapItem(void *const context, struct hashmap_element_s *const e) {
    free(e->data);
    return -1;
}

const char* getJSONString(JsonNode *item, const char* key) {
    // Get key
    JsonNode *node = json_find_member(item, key);
    const char *result = "";
    if ( node != NULL && node->tag == JSON_STRING) {
        result = node->string_;
    }
    return result;
}

bool getJSONBool(JsonNode *item, const char* key, bool *result) {
    JsonNode *node = json_find_member(item, key);
    if ( node != NULL && node->tag == JSON_BOOL) {
        *result = node->bool_;
        return true;
    }
    return false;
}

bool getJSONInt(JsonNode *item, const char* key, int *result) {
    JsonNode *node = json_find_member(item, key);
    if ( node != NULL && node->tag == JSON_NUMBER) {
        *result = (int) node->number_;
        return true;
    }
    return false;
}

#endif //ASSETS_C_COMMON_H
