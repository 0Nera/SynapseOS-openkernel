/**
 * @file arch.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


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