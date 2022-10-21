/**
 * @file int.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Функции обработки прерываний
 * @version 0.1.0
 * @date 21-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef	_INT_H
#define	_INT_H	1


/**
 * @brief Максимальное количество векторов прерываний (1023 + 1)
 * 
 */
#define INTERRUPT_MAX_INDEX 1023

bool int_set_handler(uint16_t index, void *func);


#endif // int.h