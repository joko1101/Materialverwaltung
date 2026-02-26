// Autor: Joachim Schneider

#include "ringlist.h"

tList* lCreate(int (*cmp)(const void* pEl1, const void* pEl2), int (*delEl)(void* pElement))
{
    tList* list = malloc(sizeof(tList));
    if (!list) return NULL; // Allocation failed
    tCnct* cnct = malloc(sizeof(tCnct));
    if (!cnct) return NULL; // Allocation failed
    cnct->pNext = cnct;
    cnct->pPrev = cnct;
    cnct->pData = NULL;
    list->pHead = cnct;
    list->length = 0;
    list->cmp = cmp;
    list->delEl = delEl;
    return list;
}

int lDelete(tList* pList)
{
    if (pList->length == 1)
    {
        pList->delEl(pList->pHead->pData);
        free(pList->pHead);
        free(pList);
        return 0;
    }

    pList->pCurr = pList->pHead->pNext;
    while (pList->pCurr != pList->pHead)
    {
        pList->pCurr = pList->pCurr->pNext;
        if (!pList->delEl(pList->pCurr->pPrev->pData));
            free(pList->pCurr->pPrev);
    }
    pList->delEl(pList->pHead->pData);
    free(pList->pHead);
    
    free(pList);
    pList = NULL;

    return 0;
}

int lInsertBehind(tCnct* pTarget, void* pElement)
{
    tCnct *new_el = malloc(sizeof(tCnct));
    if (!new_el) return 1; // Allocation failed
    new_el->pData = pElement;
    new_el->pPrev = pTarget;
    new_el->pNext = pTarget->pNext;

    // WATCH OUT: Order is important! Otherwise pPrev links to itself!
    pTarget->pNext->pPrev = new_el;
    pTarget->pNext = new_el;
    
    return 0;
}

int lInsert(tList* pList, void* pElement)
{
    int err = 0;

    if (lEmtpy(pList)) pList->pHead->pData = pElement; // If list is empty, insert as first element (list head)
    else if (!pList->cmp) err = lAppend(pList, pElement); // If comparison function is not set, append to end of list (no sorting)
    else if (pList->cmp(pList->pHead->pData, pElement) > 0) // If element is smaller than first
        {
            err = lInsertBehind(pList->pHead->pPrev, pElement);
            pList->pHead = pList->pHead->pPrev; // Update head pointer
        }
    else
    {
        pList->pCurr = pList->pHead;
        {
            // Sorted insert between 2 elements
            do
            {
                if (pList->pCurr->pNext == pList->pHead) 
                {
                    err = lAppend(pList, pElement); // If end of list reached, element is largest, append at end
                    break;
                }
                else if (
                    pList->cmp(pList->pCurr->pData, pElement) <= 0 && 
                    pList->cmp(pList->pCurr->pNext->pData, pElement) > 0)
                    {
                        err = lInsertBehind(pList->pCurr, pElement);
                        break;
                    }
                pList->pCurr = pList->pCurr->pNext;
            } while (pList->pCurr != pList->pHead);
        }
    }
    if (!err) pList->length++;
    return err;
}

int lAppend(tList* pList, void* pElement)
{
    if (lEmtpy(pList)) pList->pHead->pData = pElement;
    else return lInsertBehind(pList->pHead->pPrev, pElement);
    return 0;
}

int lRemove(tList* pList, void* pElement)
{
    pList->pCurr = pList->pHead;
    do
    {
        if (pList->pCurr->pData == pElement)
        {
            pList->pCurr->pPrev->pNext = pList->pCurr->pNext;
            pList->pCurr->pNext->pPrev = pList->pCurr->pPrev;
            pList->delEl(pList->pCurr->pData);
            if (pList->pCurr == pList->pHead) pList->pHead = pList->pCurr->pNext; // Update head pointer if head is removed
            free(pList->pCurr);
            pList->length--;
            return 0;
        }
        pList->pCurr = pList->pCurr->pNext;
    }
    while (pList->pCurr != pList->pHead);
    return 1;
}

void* lGet(tList* pList, const void* filter_val, int (*filter)(const void* pEl1, const void* filter_val))
{
    if (pList->length == 0) return NULL;
    pList->pCurr = pList->pHead;
    do
    {
        if (filter(pList->pCurr->pData, filter_val) == 0)
            return pList->pCurr->pData;
        pList->pCurr = pList->pCurr->pNext;
    }
    while (pList->pCurr != pList->pHead);
    return NULL;
}

void* lGetByIndex(tList* pList, int index)
{
    if (index < 0 || index >= pList->length) return NULL;
    pList->pCurr = pList->pHead;
    for (int i=0; i<index; i++)
        pList->pCurr = pList->pCurr->pNext;
    return pList->pCurr->pData;
}

void lToArray(tList* pList, void *targetArr[])
{
    pList->pCurr = pList->pHead;
    int i=0;
    do
    {
        targetArr[i++] = pList->pCurr->pData;
        pList->pCurr = pList->pCurr->pNext;
    } while (pList->pCurr != pList->pHead);
}

void lPrintAll(tList* pList, void (*formprint)(const void* pData))
{
    printf("\n");
    pList->pCurr = pList->pHead;
    do
    {
        formprint(pList->pCurr->pData);
        pList->pCurr = pList->pCurr->pNext;
    }
    while (pList->pCurr != pList->pHead);
}

int lEmtpy(tList* pList)
{
    return (!pList->pHead->pData);
}