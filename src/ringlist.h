#ifndef _RINGLIST_H_
#define _RINGLIST_H_

// Autor: Joachim Schneider

#include "util.h"

typedef struct cnct {
    struct cnct* pNext;
    struct cnct* pPrev;
    void* pData;
} tCnct;

typedef struct list {
    tCnct* pHead;
    tCnct* pCurr;
    int length;
    int (*cmp)(const void* pEl1, const void* pEl2);
    int (*delEl)(void* pElement);
} tList;

// Initialize a ring list; If argument 'cmp' is set, list will be sorted accordingly on every operation, if not, elements will be added to the end
tList* lCreate(int (*cmp)(const void* pEl1, const void* pEl2), int (*delEl)(void* pElement));   

// Delete a ring list
int lDelete(tList* pList);

// Insert new element behind concrete element
int lInsertBehind(tCnct* pTarget, void* pElement);

// Add an element to a ring list
int lAppend(tList* pList, void* pElement);

// Insert element according to list sorting
int lInsert(tList* pList, void* pElement);

// Remove an element from a ring list
int lRemove(tList* pList, void *pElement);

// Get an element from a ring list
void* lGet(tList* pList, const void* filter_val, int (*filter)(const void* pElement, const void* filter_val));

// Get an element from a ring list by index
void *lGetByIndex(tList* pList, int index);

// Convert list to array; Argument 'size' is size the datatype
void lToArray(tList* pList, void *targetArr[]);

// Print an entire list
void lPrintAll(tList* list, void (*formprint)(const void* pData));

int lEmtpy(tList* list);

#endif // _RINGLIST_H_