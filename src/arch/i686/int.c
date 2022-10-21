/**
 * @file int.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Функции обработки прерываний
 * @version 0.1.0
 * @date 21-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>
#include <tools.h>
#include <com1_log.h>
#include <arch.h>
#include <int.h>


/**
 * @brief Изменения функции для вектора прерывания
 * 
 * @param index Номер вектора
 * @param func Указатель на функцию
 * @return true В случае успеха
 * @return false В случае если index вне диапазона от 0 до 1023
 */
bool int_set_handler(uint16_t index, void *func) {
    if (index > INTERRUPT_MAX_INDEX) {
        com1_log("index %d is more than %d", index, INTERRUPT_MAX_INDEX);
        return false;
    }

    UNUSED(func);

    return true;
}