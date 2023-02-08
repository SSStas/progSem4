#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cWord.h"


CWord *createWord(char *text) {
    CWord *word = (CWord*) calloc(1, sizeof(CWord));
    word->text = text;
    word->length = strlen(text);

    return word;
}

int comp(const CWord *i, const CWord *j) {
    return strcmp(i->text, j->text);
}

char *getDictType(void *dict) {
    CDict *cDict = (CDict*) dict;

    return cDict->type;
}

void *createDict() {
    CDict *dict = (CDict*) calloc(1, sizeof(CDict));;
    dict->count = 0;
    dict->maxSize = 100;
    dict->type = "cWord";
    dict->list = (CWord*) calloc(100, sizeof(CWord));

    return dict;
}

void *resizeDict(void *dict) {
    CDict *cDict = (CDict*) dict;
    CWord *oldCList = cDict->list;

    if (cDict->count >= cDict->maxSize) {
        cDict->list = (CWord*) realloc(cDict->list, cDict->maxSize + 100 * sizeof(CWord));
        if(cDict->list == NULL) {
            free(oldCList);
            printf("wordsFrequency:cWord.h: Allocation error\n");
            exit (1);
        }
        cDict->maxSize += 100;
    }

    return cDict;
}

int findWord(void *dict, char *text) {
    CDict *cDict = (CDict*) dict;

    for (int i = 0; i < cDict->count; ++i) {
        if (!strcmp(cDict->list[i].text, text)) {
            return 1;
        }
    }

    return 0;
}

int checkWord(char *text) {
    for (int i = 0; i < strlen(text); ++i) {
        if (isdigit(text[i]) || !isalpha(text[i])) {
            return 1;
        }
    }
    return 0;
}

void addWord(void *dict, char *text) {
    CDict *cDict = (CDict*) dict;
    CWord *word = createWord(text);

    if (findWord(dict, text) || !checkWord(text)) {
        return;
    }

    if (cDict->count + 1 >= cDict->maxSize) {
        cDict = (CDict*) resizeDict(cDict);
    }
    cDict->list[cDict->count] = *word;
    cDict->count++;

    free(word);
}

void sortWords(void *dict) {
    CDict *cDict = (CDict*) dict;
    qsort(cDict->list, cDict->count, sizeof(CWord), (int(*) (const void *, const void *)) comp);
}

void showDict(void *dict) {
    CDict *cDict = (CDict*) dict;

    printf("%s dictionary: \n", cDict->type);
    for (int i = 0; i < cDict->count; ++i) {
        printf("%s\n", cDict->list[i].text);
    }
    printf("\n");
}

void freeDict(void *dict) {
    CDict *cDict = (CDict*) dict;

    free(cDict->list);
    free(cDict);
}
