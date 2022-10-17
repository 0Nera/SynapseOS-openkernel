/**
 * @file arch.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 17-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */

#pragma once

#ifdef __i386__
#define halt() asm volatile("hlt")
#endif

#ifdef __x86_64__
#define halt() asm volatile("hlt")
#endif