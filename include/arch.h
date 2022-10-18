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

#ifdef __i386__
#define halt() asm volatile("hlt")

/**
 * @brief Получение размера ядра
 * 
 * @return unsigned int размер ядра
 */
unsigned int arch_get_kernel_size() {
    unsigned int temp_size = 0;

    asm volatile (
        ""
        : "=d" (temp_size)
    );

    return temp_size;
}

#endif

#ifdef __x86_64__
#define halt() asm volatile("hlt")

/**
 * @brief Получение размера ядра
 * 
 * @return unsigned int размер ядра
 */
unsigned int arch_get_kernel_size() {
    unsigned int temp_size = 0;

    asm volatile (
        ""
        : "=d" (temp_size)
    );

    return temp_size;
}
#endif

#endif // arch.h