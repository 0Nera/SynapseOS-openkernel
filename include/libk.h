/**
 * @file libk.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Стандартная библиотека ядра
 * @version 0.1.0
 * @date 18-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef	_LIBK_H
#define	_LIBK_H	1


/**
 * @brief Используем встроенный в GCC тип для функций которые не возвращают ничего
 * 
 */
#define noreturn _Noreturn


/**
 * @brief Инициализация AP до использования макросами va_arg и va_end.
 * 
 */
#define va_start(v,l)	__builtin_va_start(v,l)


/**
 * @brief Освобождение памяти va_list
 * 
 */
#define va_end(v)	__builtin_va_end(v)


/**
 * @brief Парсинг аргументов va_list
 * 
 */
#define va_arg(v,l)	__builtin_va_arg(v,l)


/**
 * @brief Копирование va_list
 * 
 */
#define va_copy(d,s)	__builtin_va_copy(d,s)


/**
 * @brief Поиск наибольшего числа
 * 
 */
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })


/**
 * @brief Верно
 * 
 */
#define true 1


/**
 * @brief Ложь
 * 
 */
#define false 0


/**
 * @brief Реализация NULL
 * 
 */
#define NULL ((void *)0)


/**
 * @brief Число от 0 до 255 (1 байт)
 * 
 */
typedef unsigned char uint8_t;


/**
 * @brief Число от 0 до 65536 (2 байта)
 * 
 */
typedef unsigned short uint16_t;


/**
 * @brief Число от 0 до 4294967296 (4 байта)
 * 
 */
typedef unsigned int uint32_t;



/**
 * @brief Специальный тип указателей
 * 
 */
typedef __UINTPTR_TYPE__ uintptr_t;


/**
 * @brief Специальный тип для булевых операций
 * 
 */
typedef _Bool bool;


/**
 * @brief Список аргументов
 * 
 */
typedef __builtin_va_list va_list;


uint32_t strlen(const char *string);


bool multiboot2_init(unsigned int addr);

#endif  // libk.h