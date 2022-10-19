/**
 * @file kernel.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Главный файл ядра
 * @version 0.1.0
 * @date 17-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <arch.h>
#include <com1_log.h>
#include <libk.h>
#include <multiboot2.h>
#include <ports.h>
#include <tools.h>


/**
 * @brief Размер ядра
 * 
 */
unsigned int kernel_size = 0;


/**
 * @brief Функция инициализации ядра
 * 
 * @param eax Магическое число
 * @param ebx Указатель на данные загрузчика
 * @param esp Стек
 */
noreturn void kernel_startup(unsigned int eax, unsigned int ebx, unsigned int esp) {
    kernel_size = arch_get_kernel_size();

    // До интеграции multiboot2 они бесполезны
    UNUSED(ebx);
    UNUSED(esp);

    com1_log("Kernel ready, %x == %x", eax, MULTIBOOT2_BOOTLOADER_MAGIC);
    
    unit_test(eax == MULTIBOOT2_BOOTLOADER_MAGIC, "Check bootloader magic");

    // Останавливаем процессор
    for (;;) {
        halt();
    }
}