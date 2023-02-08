#pragma once


typedef struct CWord {
    char *text;
    int length;
} CWord; 

typedef struct CDict {
    char *type;
    CWord *list;
    int count; 
    int maxSize;
} CDict;

char *getDictType(void *dict);

void *createDict();

void *resizeDict(void *dict);

int findWord(void *dict, char *text);

int checkWord(char *text);

void addWord(void *dict, char *text);

void sortWords(void *dict);

void showDict(void *dict);

void freeDict(void *dict);
