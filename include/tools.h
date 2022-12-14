/**
 * @file tools.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Дополнительные утилиты для упрощения написания кода
 * @version 0.1.0
 * @date 18-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef _TOOLS_H
#define _TOOLS_H 1


/**
 * @brief Для неиспользуемых переменных
 * 
 */
#define UNUSED(x) (void)(x)


/**
 * @brief Логическое ИЛИ
 * 
 */
#define OR ||


/**
 * @brief Логическое И
 * 
 */
#define AND &&


/**
 * @brief Инверсия
 * 
 */
#define NOT(x) !(x)


#endif