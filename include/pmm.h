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


#include <arch.h>
#include <libk.h>
#include <multiboot2.h>


#ifndef	_PMM_H
#define	_PMM_H	1


#if (defined __i386__ || defined __x86_64__)



#define BLOCK_SIZE 4096
#define BLOCKS_PER_BUCKET 8
#define BLOCK_ALIGN(addr) (((addr) & 0xFFFFF000) + 0x1000)
#define SETBIT(i) pmm_bitmap[i / BLOCKS_PER_BUCKET] = pmm_bitmap[i / BLOCKS_PER_BUCKET] | (1 << (i % BLOCKS_PER_BUCKET))
#define CLEARBIT(i) pmm_bitmap[i / BLOCKS_PER_BUCKET] = pmm_bitmap[i / BLOCKS_PER_BUCKET] & (~(1 << (i % BLOCKS_PER_BUCKET)))
#define ISSET(i) ((pmm_bitmap[i / BLOCKS_PER_BUCKET] >> (i % BLOCKS_PER_BUCKET)) & 0x1)
#define GET_BUCKET32(i) (*((uint32_t*) &pmm_bitmap[i / 32]))


uint32_t pmm_find_free_block();
bool pmm_init();


#endif 


#endif // pmm.h