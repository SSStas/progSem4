#pragma once

void createHandles(void **handles, char **args, int count);

void createDicts(void **handles, void **dicts, int count);

void addWordsIntoDicts(void **handles, char *text, void **dicts, int count);

void sortDicts(void **handles, void **dicts, int count);

void showDicts(void **handles, void **dicts, int count);

void freeDicts(void **handles, void **dicts, int count);

void freeHandles(void **handles, int count);
