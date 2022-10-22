/**
 * @file arch.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Архитектурно-зависимые функции
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <arch.h>
#include <com1_log.h>


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


/**
 * @brief Отладочная функция для тестирования CPUID
 * 
 */
void arch_cpuid_test() {
    for (int i = 0; i < 5; i++) {
        char string[11] = {0};
        int pos = 0;
        int eax, ebx, edx, ecx;

        asm volatile(
            "mov %1, %%eax; "            // Ввод
            "cpuid;"
            "mov %%eax, %0;"             // Записываем вывод
            :
            "=r"(eax),                   // eax на выход
            "=b"(ebx),
            "=d"(edx),
            "=c"(ecx)
            :"r"(i)                      // eax на вход
            );
        
        com1_log("cpuid eax %x ebx %x edx %x ecx %x", eax, ebx, edx, ecx);
        

        for (int shifted = 0; shifted < 0x20; shifted += 8) {
            int mask = 0xFF << shifted;
            int matched = (ebx & mask) >> shifted;
            string[pos] = matched;
            pos++;
        }

        for (int shifted = 0; shifted < 0x20; shifted += 8) {
            int mask = 0xFF << shifted;
            int matched = (edx & mask) >> shifted;
            string[pos] = matched;
            pos++;
        }

        for (int shifted = 0; shifted < 0x20; shifted += 8) {
            int mask = 0xFF << shifted;
            int matched = (ecx & mask) >> shifted;
            string[pos] = matched;
            pos++;
        }

        com1_log("cpuid decode: [%s] pos = %d", string, pos);
    }
}