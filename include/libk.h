/**
 * @file libk.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 18-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#ifndef	_LIBK_H
#define	_LIBK_H	1


#define noreturn _Noreturn

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#define va_copy(d,s)	__builtin_va_copy(d,s)
#define __va_copy(d,s)	__builtin_va_copy(d,s)

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;


#endif  // libk.h