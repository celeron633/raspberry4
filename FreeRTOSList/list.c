#include "list.h"
#include <stdio.h>

void vListInitialise(List_t * const pxList)
{
    pxList->uxNumberOfItems     = 0U;
    pxList->pxIndex             = (ListItem_t *)&(pxList->xListEnd);
    pxList->xListEnd.pxNext     = (ListItem_t *)&(pxList->xListEnd);
    pxList->xListEnd.pxPrevious = (ListItem_t *)&(pxList->xListEnd);
    pxList->xListEnd.xItemValue = portMAX_DELAY;
}

void vListInitialiseItem(ListItem_t * const pxItem)
{
    pxItem->xItemValue  = 0U;
    pxItem->pvOwner     = NULL;
    pxItem->pxContainer = NULL;
    pxItem->pxNext      = NULL;
    pxItem->pxPrevious  = NULL;
    pxItem->xItemValue  = 0U;
}

void vListInsertEnd(List_t * const pxList, ListItem_t * const pxNewListItem)
{
    pxNewListItem->pxContainer = pxList;
    
    ListItem_t *pxIterator = pxList->xListEnd.pxPrevious;

    pxNewListItem->pxNext               = pxIterator->pxNext;
    pxNewListItem->pxNext->pxPrevious   = pxNewListItem;
    pxIterator->pxNext                  = pxNewListItem;
    pxNewListItem->pxPrevious           = pxIterator;
}