#include <stdio.h>
#include <unistd.h>

#include "list.h"


List_t list;
ListItem_t listItem1;
ListItem_t listItem2;
ListItem_t listItem3;

int main()
{
    fprintf(stderr, "hello world\r\n");

    vListInitialise(&list);
    vListInitialiseItem(&listItem1);
    vListInitialiseItem(&listItem2);
    vListInitialiseItem(&listItem3);

    listItem1.pvOwner = (void *)0;
    listItem1.pxContainer = &list;
    listItem1.xItemValue = 10;

    listItem2.pvOwner = (void *)0;
    listItem2.pxContainer = &list;
    listItem2.xItemValue = 20;

    listItem3.pvOwner = (void *)0;
    listItem3.pxContainer = &list;
    listItem3.xItemValue = 30;

    vListInsertEnd(&list, &listItem1);
    vListInsertEnd(&list, &listItem2);
    vListInsertEnd(&list, &listItem3);

    ListItem_t *pxIteratorEnd = list.xListEnd.pxPrevious;
    ListItem_t *pxIteratorBegin = list.xListEnd.pxNext;

    for (ListItem_t *it = pxIteratorBegin; it != pxIteratorEnd->pxNext ; it = it->pxNext)
    {
        printf("ItemValue: [%d]\r\n", it->xItemValue);
        usleep(500 * 1000);
    }

    return 0;
}