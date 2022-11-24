/**
 * @file libk.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Функции для упрощения написания кода ядра
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
    uint32_t length = 0;

    while(string[length]) {
        length++;
    }

    return length;
}


/**
 * @brief Заполнение памяти байтом
 * 
 * @param address Адресс области
 * @param value Байт заполнения
 * @param length Длина области
 */
void memset(void *address, uint8_t value, uint32_t length) {
    uint8_t *array = (uint8_t*)address;

    for (uint32_t i = 0; i < length; i++) {
        array[i] = value; 
    }
}


/**
 * @brief Проверка соответствия строк
 * 
 * @param string1 Первая сравниваемая строка 
 * @param string2 Вторая сравниваемая строка
 * @return int 0 - в случае успеха, 1 в случае если string1 > string2 и -1 в случае если string1 < string2
 */
int strcmp(char *string1, char *string2) {
    // Пока строки одинаковые сравнивать нечего
    while(*string1++ == *string2++);

    if(*string1 == *string2) {
        return 0;   // Строки совпали
    } else if(*string1 < *string2) {
        return -1;  // string1 < string2
    }

    return 1;       // string1 > string2
}
