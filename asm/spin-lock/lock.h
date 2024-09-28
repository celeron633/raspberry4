#ifndef __LOCK_H__
#define __LOCK_H__

typedef struct lock_t
{
    // 0: unlocked, 1: locked
    int l;
} lock_t;

void lock_init(lock_t *lock);
void lock(lock_t *lock);
void unlock(lock_t *lock);

#endif