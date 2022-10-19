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


#endif // arch.h