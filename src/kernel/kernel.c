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
#include <dt.h>
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
    kernel_size =  ((uint32_t) &KERNEL_SIZE) >> 10;

    // Стек пока не используем
    UNUSED(esp);

    com1_log("Kernel ready, magic %x", eax);
    com1_log("Mbi %x", ebx);
    com1_log("kernel size %ukb (with stack)", kernel_size);

    unit_test(eax == MULTIBOOT2_BOOTLOADER_MAGIC, "Check bootloader magic");
    unit_test(ebx & 7, "Unaligned mbi check");

    unit_test(multiboot2_init(ebx), "Check multiboot2 work");
 
    unit_test(dt_init(), "Setup descriptor tables");

    // Останавливаем процессор
    for (;;) {
        halt();
    }
}