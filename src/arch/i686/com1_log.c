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


static const char CONVERSION_TABLE[] = "0123456789ABCDEF";


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
static void com1_log_printdec(long num) {
    if (!num) {
        com1_log_putchar('0');
        return;
    }

    int size = 0;
    int t = num;

    while(t / 10 != 0) {
        t = t/10;
        size++;
    }

    char ret[64];

    size++;
    ret[size] = '\0';
    t = num;
    int i = size - 1;

    while(i >= 0) {
        ret[i] = (t % 10) + '0';
        t = t/10;
        i--;
    }

    com1_log_puts(ret);
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
 * @brief 
 * 
 * @param address 
 * @param size 
 */
void com1_log_dump(void *address, uint32_t size) {
    /* Преобразуем указатель в массив байт */
    uint8_t *dump = (uint8_t*) address; 
    /* Преобразуем указатель просто в число */  
    uint32_t addr_tmp = (uint32_t) address;
    /* Вспомогательные переменные */
    uint32_t mark = 0;
    
    for (uint32_t i = 0; i < size; i++) {
    
        if (mark == 0) {
            com1_log_printhex(addr_tmp);
            com1_log_puts(": ");
        }
    
        com1_log_printhex(dump[i]);
    
        switch(mark) {
            case 7:
                com1_log_putchar('|');
                mark++;
                break;
            case 16:
                com1_log_putchar('\n');
                mark = 0;
                addr_tmp += 0x10;
                break;
            default:
                com1_log_putchar(' ');
                mark++;
                break;
        }
    }
    com1_log_putchar('\n');
}



static int com1_log_powk(int x, unsigned int y) {
    if( y == 0)
        return 1;
    else if (y%2 == 0)
        return com1_log_powk(x, y/2)*com1_log_powk(x, y/2);
    else
        return x*com1_log_powk(x, y/2)*com1_log_powk(x, y/2);
 
}
 

static void com1_log_printfloat(double num, int after_point) {
    int int_float = (int) num;
    com1_log_printdec(int_float);
    com1_log_putchar('.');
    
    int mut_ab = com1_log_powk(10,after_point);
    int after_point_float = (int) (num * mut_ab); //33314
    
    int multiplier = com1_log_powk(10,(after_point-1));
    //printf("MULTIPLIER : %d\n" , multiplier);
    for(int xy=0; xy<after_point; xy++) {
        int muted = (after_point_float/multiplier);
        //printf("%d\n",muted);
        muted = muted % 10;
        com1_log_printdec(muted);
        
        multiplier/=10;
    }
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
            } else if (*format_string == '8') {
                com1_log_printdec((unsigned char)va_arg(args, char*)[0]);
            } else if (*format_string == 'd') {
                com1_log_printdec(va_arg(args, long));
            } else if (*format_string == 'f') {
                com1_log_printfloat(va_arg(args, double), 7);
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