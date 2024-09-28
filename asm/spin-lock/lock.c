#include "lock.h"
#include "atomic.h"

void lock_init(lock_t *lock)
{
    lock->l = 0;
}

void lock(lock_t *lock)
{
    // a_cas返回的是上锁之前的值
    while(a_cas(&(lock->l), 0, 1));
}

void unlock(lock_t *lock)
{
#if 0
    while(a_cas(&(lock->l), 1, 0) == 1);
#endif

    a_store(&(lock->l), 0);
}