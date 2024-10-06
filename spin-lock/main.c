#include "atomic.h"
#include "lock.h"

#include <stdio.h>
#include <pthread.h>

int g_sum = 0;

lock_t g_lock;

void* threadFunc(void *arg)
{
    (void)arg;

    for (int i = 0; i < 100000; i++) {
        lock(&g_lock);
        g_sum += 1;
        unlock(&g_lock);
    }

    return NULL;
}

int main()
{
    lock_init(&g_lock);

    pthread_t th;
    pthread_create(&th, NULL, threadFunc, NULL);

    for (int i = 0; i < 100000; i++) {
        lock(&g_lock);
        g_sum += 1;
        unlock(&g_lock);
    }
    pthread_join(th, NULL);

    printf("g_sum=%d\r\n", g_sum);

    return 0;
}