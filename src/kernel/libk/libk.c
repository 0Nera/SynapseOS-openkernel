/**
 * @file libk.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>


/**
 * @brief Вычисление длины строки
 * 
 * @param string Строка
 * @return uint32_t Длина строки
 */
uint32_t strlen(const char *string) {
    uint32_t lenght = 0;

    while(string[lenght]) {
        lenght++;
    }

    return lenght;
}