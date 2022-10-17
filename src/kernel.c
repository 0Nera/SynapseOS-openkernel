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
#include <stdint.h>

/**
 * @brief Это x86 VGA буффер. 25 строк по 80 символов.
 * 
 */
volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;


/**
 * @brief Функция инициализации ядра
 * 
 * @param eax Магическое число
 * @param ebx Указатель на данные загрузчика
 * @param esp Стек
 */
void kernel_startup(unsigned int eax, unsigned int ebx, unsigned int esp) {
    unsigned int kernel_size = 0;

    // Узнаем размер ядра
    asm volatile (
        ""
        : "=d" (kernel_size)
    );

    // Очистка экрана
	for (int col = 0; col < 80; col ++) {
		for (int row = 0; row < 25; row ++) {
			const int index = (80 * row) + col;
			vga_buffer[index] = ((uint16_t)0x0F << 8) | ' ';
		}
	}

    // Останавливаем процессор
    for (;;) {
        halt();
    }
}