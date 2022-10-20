/**
 * @file com1_log.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Функции для работы с com1 портом
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <com1_log.h>
#include <libk.h>
#include <ports.h>
#include <tools.h>


static const char CONVERSION_TABLE[] = "0123456789abcdef";


/**
 * @brief Проверка "занятости" COM1 порта
 * 
 * @return int Количество задач
 */
static int com1_log_is_transmit_empty() {
    return ports_inb(PORTS_COM1 + 5) & 0x20;
}


/**
 * @brief Вывод символа в COM1 порт
 * 
 * @param c Выводимый символ
 */
static void com1_log_putchar(char c) {
    while (com1_log_is_transmit_empty() == 0);
    ports_outb(PORTS_COM1, c);
}


/**
 * @brief Вывод строки в COM1 порт
 * 
 * @param string Выводимая строка
 */
static void com1_log_puts(const char string[]) {
    for (uint32_t i = 0; i < strlen(string); i++) {
        com1_log_putchar(string[i]);
    }
}


/**
 * @brief Вывод шестнадцатеричного числа в COM1 порт
 * 
 * @param num Выводимое число
 */
static void com1_log_printhex(int num) {
    int i;
    char buf[17];

    if (!num) {
        com1_log_puts("0x0");
        return;
    }

    buf[16] = 0;

    for (i = 15; num; i--) {
        buf[i] = CONVERSION_TABLE[num % 16];
        num /= 16;
    }

    i++;
    com1_log_puts("0x");
    com1_log_puts(&buf[i]);
}


/**
 * @brief Вывод десятичного числа в COM1 порт
 * 
 * @param num Выводимое число
 */
static void com1_log_printdec(int num) {
    int i;
    char buf[21] = {0};

    if (!num) {
        com1_log_putchar('0');
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    com1_log_puts(buf + i);
}


/**
 * @brief Вывод десятичного числа больше нуля в COM1 порт
 * 
 * @param num Выводимое число
 */
static void com1_log_printudec(unsigned int num) {
    int i;
    char buf[21] = {0};

    if (!num) {
        com1_log_putchar('0');
        return;
    }

    for (i = 19; num; i--) {
        buf[i] = (num % 10) + 0x30;
        num = num / 10;
    }

    i++;
    com1_log_puts(buf + i);
}



/**
 * @brief Вывод в COM1 порт форматированной строки используя неопределенное количество аргументов
 * 
 * @param format_string Строка форматов
 * @param ... Аргументы
 */
void com1_log_printf(const char *format_string, ...) {
    va_list args;

    // Ищем первый аргумент
    va_start(args, format_string);

    // Обработка и парсинг строки форматов
    while (*format_string != '\0') {
        if (*format_string == '%') {
            format_string++;
            if (*format_string == 'x') {
                com1_log_printhex(va_arg(args, int));
            } else if (*format_string == 'd') {
                com1_log_printdec(va_arg(args, int));
            } else if (*format_string == 'u') {
                com1_log_printudec(va_arg(args, unsigned int));
            } else if (*format_string == 's') {
                com1_log_puts(va_arg(args, char*));
            } else if (*format_string == 'c') {
                com1_log_putchar((char)va_arg(args, char*)[0]);
            }
        } else {
            com1_log_putchar(*format_string);
        }
        format_string++;
    }
    
    // Освобождаем память
    va_end(args);
}