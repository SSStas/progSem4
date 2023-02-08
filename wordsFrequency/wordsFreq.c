#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dlfcn.h>
#include "wordsFreq.h"


void createHandles(void **handles, char **args, int count) {
    for (int i = 0; i < count; ++i) {
        handles[i] = dlopen(args[i + 1], RTLD_LAZY);
        if (!handles[i]) {
            printf("wordsFrequency:main.c: %s\n", dlerror());
            exit(1);
        }
        dlerror();
    }
}

void createDicts(void **handles, void **dicts, int count) {
    void *(*createDict)();

    for (int i = 0; i < count; ++i) {
        *(void **) (&createDict) = dlsym(handles[i], "createDict");
        dicts[i] = (*createDict)();
    }
}

void addWordIntoDicts(void **handles, char *text, void **dicts, int count) {
    void (*addWord)(void*, char*);

    for (int i = 0; i < count; ++i) {
        *(void **) (&addWord) = dlsym(handles[i], "addWord");
        (*addWord)(dicts[i], text);
    }
}

void addWordsIntoDicts(void **handles, char *text, void **dicts, int count) {

    size_t len = strlen(text);
    int isLastSpace = 1;
    char *ptr = text;

    for (int i = 0; i < len; ++i) {
        if (!isspace(text[i]) && isLastSpace) {
            ptr = text + i;
            isLastSpace = 0;
        } else if (isspace(text[i])) {
            text[i] = '\0';
            if (!isLastSpace) {
                addWordIntoDicts(handles, ptr, dicts, count);
            }
            isLastSpace = 1;
        }
    }
}

void sortDicts(void **handles, void **dicts, int count) {
    void (*sortWords)(void*);

    for (int i = 0; i < count; ++i) {
        *(void **) (&sortWords) = dlsym(handles[i], "sortWords");
        (*sortWords)(dicts[i]);
    }
}

void showDicts(void **handles, void **dicts, int count) {
    void (*showDict)(void*);

    for (int i = 0; i < count; ++i) {
        *(void **) (&showDict) = dlsym(handles[i], "showDict");
        (*showDict)(dicts[i]);
    }
}

void freeDicts(void **handles, void **dicts, int count) {
    void (*freeDict)(void*);

    for (int i = 0; i < count; ++i) {
        *(void **) (&freeDict) = dlsym(handles[i], "freeDict");
        (*freeDict)(dicts[i]);
    }
}

void freeHandles(void **handles, int count) {
    for (int i = 0; i < count; ++i) {
        dlclose(handles[i]);
    }
}
