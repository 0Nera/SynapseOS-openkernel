/**
 * @file dt.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Управление таблицами дескрипторов (idt, gdt)
 * @version 0.1.0
 * @date 21-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <arch.h>
#include <libk.h>
#include <tools.h>


#ifndef	_DT_H
#define	_DT_H	1


#include <libk.h>


#if (defined __i386__ || defined __x86_64__)


bool dt_init();


#endif



#endif // dt.h