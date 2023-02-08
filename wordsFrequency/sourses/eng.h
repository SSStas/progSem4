#pragma once


typedef struct EngWord {
    char *text;
    int length;
} EngWord; 

typedef struct EngDict {
    char *type;
    EngWord *list;
    int count; 
    int maxSize;
} EngDict;

char *getDictType(void *dict);

void *createDict();

void *resizeDict(void *dict);

int findWord(void *dict, char *text);

int checkWord(char *text);

void addWord(void *dict, char *text);

void sortWords(void *dict);

void showDict(void *dict);

void freeDict(void *dict);
