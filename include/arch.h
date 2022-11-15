/**
 * @file arch.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Архитектурно-зависимые функции
 * @version 0.1.0
 * @date 17-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef    _ARCH_H
#define    _ARCH_H    1


#include <libk.h>


#if (defined __i386__ || defined __x86_64__)

#define halt() asm volatile("hlt")

#define KERNEL_OFFSET 0xC0000000

#define V2P(a) ((uintptr_t)(a) & ~KERNEL_OFFSET)
#define P2V(a) ((uintptr_t)(a) | KERNEL_OFFSET)


extern uintptr_t KERNEL_BEGIN_PHYS;
extern uintptr_t KERNEL_END_PHYS;
extern uintptr_t KERNEL_START;
extern uintptr_t KERNEL_END;
extern uintptr_t KERNEL_SIZE;

unsigned int arch_get_kernel_size();
void arch_cpuid_test();
bool fpu_init();

#endif


#if defined(__i386__)

static inline unsigned long long rdtsc() {
    unsigned long long int x;
    asm volatile (".byte 0x0f, 0x31" : "=A" (x));
    return x;
}

#elif defined(__x86_64__)

static inline unsigned long long rdtsc() {
    unsigned hi, lo;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif

#endif // arch.h