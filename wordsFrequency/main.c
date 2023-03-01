#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <dlfcn.h>
#include "wordsFreq.h"


int main(int argc, char **argv) {
    if (argc <= 1) {
        printf("wordsFrequency:main.c: Arguments error\n");
        exit(1);
    }
 
    void *handles[argc - 1];
    void *dicts[argc - 1];
    char *line = NULL;
    size_t len = 0;
    
    createHandles(handles, argv, argc - 1);
    createDicts(handles, dicts, argc - 1);

    if (getline(&line, &len, stdin) == -1) {
        printf("wordsFrequency:main.c: Read line error\n");
        exit(1);
    }

    addWordsIntoDicts(handles, line, dicts, argc - 1);

    sortDicts(handles, dicts, argc - 1);
    showDicts(handles, dicts, argc - 1);

    freeDicts(handles, dicts, argc - 1);
    freeHandles(handles, argc - 1);
    free(line);

    return 0;
}
