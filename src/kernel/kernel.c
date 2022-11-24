/**
 * @file kernel.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Главный файл ядра
 * @version 0.3.12
 * @date 17-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <arch.h>       // Архитектурнозависимые функции
#include <dt.h>         // Таблицы дескрипторов
#include <com1_log.h>   // Отладка и работа с com1 портом
#include <libk.h>       // Библиотека ядра
#include <multiboot2.h> // Multiboot2
#include <pmm.h>        // Менеджер физической памяти
#include <ports.h>      // IO порты
#include <tools.h>      // Дополнительные функции


/**
 * @brief Размер ядра
 * 
 */
unsigned int kernel_size = 0;


/**
 * @brief Адресс фреймбуффера ядра
 * 
 */
uint8_t *kernel_framebuffer = NULL;


/**
 * @brief Функция инициализации ядра
 * 
 * @param eax Магическое число
 * @param ebx Указатель на данные загрузчика
 * @param esp Стек
 */
noreturn void kernel_startup(unsigned int eax, unsigned int ebx, unsigned int esp) {
    kernel_size = ((uint32_t)&KERNEL_SIZE) >> 10;  // Размер ядра делим на 1024, получая размер в килобайтах.

    // ESP пока не используем, стек позже пригодится при переходе в ring3
    UNUSED(esp);

    com1_log("Ядро SynapseOS 0.3.12 готово, eax %x", eax);
    com1_log("Структура multiboot2 %x", ebx);
    com1_log("Размер ядра(вместе со стеком) %u килобайт, %u байт", kernel_size, (uint32_t)&KERNEL_SIZE);

    unit_test(eax == MULTIBOOT2_BOOTLOADER_MAGIC, "Проверка магического числа Multiboot2");
    unit_test((ebx + 1) & 7, "Проверка multiboot2 заголовка на выравнивание");

    unit_test(multiboot2_init(ebx), "Парсинг multiboot2");

    //vesa_init();                                      - не реализовано в открытом ядре
    
    unit_test(dt_init(), "Настройка таблиц дескрипторов");
    
    unit_test(pmm_init(), "Настройка менеджера физической памяти");

    //arch_cpuid_test();
    
    unit_test(fpu_init(), "Настройка FPU");

    // Инициализация нейросетевого интерфейса
    //neural_main();                                    - не реализовано в открытом ядре

    //subsystems_init();                                - не реализовано в открытом ядре

    //subsystem_create(&bsd_sys);                       - не реализовано в открытом ядре

    //subsystem_mount(&bsd_sys, SUBSYS_ONLY_DRIVERS);   - не реализовано в открытом ядре

    // Работа в режиме ОСРВ?
    //real_time = false;

    //task_manager_init();                              - не реализовано в открытом ядре

    //graf_install(&ui_module);                         - не реализовано на 2 этапе

    // Уменьшаем энергопотребление процессора
    for (;;) {
        halt();
    }
}