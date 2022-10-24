/**
 * @file versions.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Типы данных и функции для работы с версиями
 * @version 0.1.0
 * @date 24-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>


#ifndef	_VERSIONS_H
#define	_VERSIONS_H	1


/**
 * @brief Структура для хранения версий
 * 
 */
typedef struct {
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
} version_t;


#endif // string.h