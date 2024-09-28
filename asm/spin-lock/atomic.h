#ifndef __SPIN_H__
#define __SPIN_H__

static inline void a_barrier()
{
    asm volatile("dmb ish":::"memory");
}

static inline void a_store(volatile int *p, int v)
{
    a_barrier();
    *p = v;
    a_barrier();
}

static inline int a_ll(volatile int *p)
{
    int v = 0;

    asm volatile
    (
        "ldaxr %w0, %1"
        :"=r"(v)
        :"Q"(*p)
        :
    );

    return v;
}

static inline int a_sc(volatile int *p, int v)
{
    int r = 0;

    asm volatile
    (
        "stlxr %w0, %w2, %1"
        :"=&r"(r)
        :"Q"(*p), "r"(v)
        :"memory"
    );

    return !r;
}

// a_cas返回的是a_sc之前的值
static inline int a_cas(volatile int *p, int t, int s)
{
    int old;
    do {
        old = a_ll(p);
        if (old != t) {
            a_barrier();
            break;;
        }
    } while (!a_sc(p, s));

    return old;
}

#endif