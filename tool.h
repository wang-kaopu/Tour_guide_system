#pragma once

#include <stdlib.h>
#include <string.h>

char* concatenateStrings(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

void swapInt(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void* deleteFromArray(void* begin, size_t n, int targetLocation, size_t size) {
    if (targetLocation < 0) {
        return NULL;
    }
    memmove((char*)begin + size * targetLocation, (char*)begin + size * (targetLocation + 1), size * (n - targetLocation - 1));
    void* arr =  (void*)realloc(begin, size * (n - 1));
    if (NULL == arr) {
        return NULL;
    }
    return arr;
}