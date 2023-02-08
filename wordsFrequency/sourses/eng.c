#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eng.h"


EngWord *createWord(char *text) {
    EngWord *word = (EngWord*) calloc(1, sizeof(EngWord));
    word->text = text;
    word->length = strlen(text);

    return word;
}

int comp(const EngWord *i, const EngWord *j) {
    return strcmp(i->text, j->text);
}

char *getDictType(void *dict) {
    EngDict *englishDict = (EngDict*) dict;

    return englishDict->type;
}

void *createDict() {
    EngDict *dict = (EngDict*) calloc(1, sizeof(EngDict));;
    dict->count = 0;
    dict->maxSize = 100;
    dict->type = "English";
    dict->list = (EngWord*) calloc(100, sizeof(EngWord));

    return dict;
}

void *resizeDict(void *dict) {
    EngDict *englishDict = (EngDict*) dict;
    EngWord *oldEnglishList = englishDict->list;

    if (englishDict->count >= englishDict->maxSize) {
        englishDict->list = (EngWord*) realloc(englishDict->list, englishDict->maxSize + 100 * sizeof(EngWord));
        if(englishDict->list == NULL) {
            free(oldEnglishList);
            printf("wordsFrequency:eng.h: Allocation error\n");
            exit (1);
        }
        englishDict->maxSize += 100;
    }

    return englishDict;
}

int findWord(void *dict, char *text) {
    EngDict *englishDict = (EngDict*) dict;

    for (int i = 0; i < englishDict->count; ++i) {
        if (!strcmp(englishDict->list[i].text, text)) {
            return 1;
        }
    }

    return 0;
}

int checkWord(char *text) {
    for (int i = 0; i < strlen(text); ++i) {
        if (!(text[i] >= 'a' && text[i] <= 'z') && !(text[i] >= 'A' && text[i] <= 'Z')) {
            return 0;
        }
    }
    return 1;
}

void addWord(void *dict, char *text) {
    EngDict *englishDict = (EngDict*) dict;
    EngWord *word = createWord(text);

    if (findWord(dict, text) || !checkWord(text)) {
        return;
    }

    if (englishDict->count + 1 >= englishDict->maxSize) {
        englishDict = (EngDict*) resizeDict(englishDict);
    }
    englishDict->list[englishDict->count] = *word;
    englishDict->count++;

    free(word);
}

void sortWords(void *dict) {
    EngDict *englishDict = (EngDict*) dict;
    qsort(englishDict->list, englishDict->count, sizeof(EngWord), (int(*) (const void *, const void *)) comp);
}

void showDict(void *dict) {
    EngDict *englishDict = (EngDict*) dict;

    printf("%s dictionary: \n", englishDict->type);
    for (int i = 0; i < englishDict->count; ++i) {
        printf("%s\n", englishDict->list[i].text);
    }
    printf("\n");
}

void freeDict(void *dict) {
    EngDict *englishDict = (EngDict*) dict;

    free(englishDict->list);
    free(englishDict);
}
