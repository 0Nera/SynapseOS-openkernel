/**
 * @file pmm.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Менеджер физической памяти
 * @version 0.1.0
 * @date 20-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>
#include <multiboot2.h>


#ifndef	_PMM_H
#define	_PMM_H	1


#if (defined __i386__ || defined __x86_64__)


bool pmm_init(struct multiboot_tag *multiboot_info);


#endif 


#endif // pmm.h