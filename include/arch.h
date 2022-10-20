/**
 * @file arch.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 17-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef	_ARCH_H
#define	_ARCH_H	1


#if (defined __i386__ || defined __x86_64__)

#define halt() asm volatile("hlt")
unsigned int arch_get_kernel_size();

#endif


#if defined(__i386__)

static inline unsigned long long rdtsc(void) {
    unsigned long long int x;
    asm volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

static inline unsigned long long rdtsc(void) {
    unsigned hi, lo;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

#endif // arch.h