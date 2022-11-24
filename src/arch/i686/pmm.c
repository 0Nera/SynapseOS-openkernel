/**
 * @file pmm.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Менеджер физической памяти
 * @version 0.1.0
 * @date 20-10-2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <arch.h>
#include <pmm.h>
#include <libk.h>
#include <com1_log.h>


/**
 * @brief Битовая карта памяти
 * 
 */
uint8_t *pmm_bitmap = (uint8_t*)(&KERNEL_END);


/**
 * @brief Начало физической памяти
 * 
 */
uint8_t *pmm_mem_start;


/**
 * @brief Количество блоков физической памяти
 * 
 */
uint32_t pmm_total_blocks;


/**
 * @brief Размер битовой карты физической памяти
 * 
 */
uint32_t pmm_bitmap_size;


/**
 * @brief Вся физическая память
 * 
 */
uint32_t pmm_memory_all = 0;


/**
 * @brief Выделение блока памяти
 * 
 * @return uint32_t Память
 */
uint32_t pmm_allocate_block() {
    uint32_t free_block = pmm_find_free_block();
    SETBIT(free_block);
    return free_block;
}


/**
 * @brief Освобождение блока памяти
 * 
 * @param block Номер блока
 */
void pmm_free_block(uint32_t block) {
    CLEARBIT(block);
}


/**
 * @brief Тестирование работы менеджера физической памяти
 * 
 * @return true Все работает
 * @return false Произошла ошибка
 */
bool pmm_test() {
    com1_log("Тестирование менеджера физической памяти");

    uint32_t t1 = 0;
    void *ret = NULL;

    t1 = pmm_find_free_block();

    ret = (void*)pmm_allocate_block();

    com1_log("Первый свободный блок: %u, %x", t1, ret);
    
    pmm_free_block((uint32_t)ret);

    return true;
}


/**
 * @brief Инициализация менеджера физической памяти
 * 
 * @return true 
 * @return false 
 */
bool pmm_init() {
    uint32_t mem_size = pmm_memory_all * 1024;

    pmm_total_blocks = mem_size / BLOCK_SIZE;
    
    // При заданном объеме памяти, сколько байт нужно
    pmm_bitmap_size = pmm_total_blocks / BLOCKS_PER_BUCKET;

    if(pmm_bitmap_size * BLOCKS_PER_BUCKET < pmm_total_blocks) {
        pmm_bitmap_size++;
    }

    // Очистка битовой карты
    memset(pmm_bitmap, 0, pmm_bitmap_size);

    pmm_mem_start = (uint8_t*)BLOCK_ALIGN(((uint32_t)(pmm_bitmap + pmm_bitmap_size)));

    com1_log("Размер памяти:         %u мегабайт", mem_size / (1024 * 1024));
    com1_log("Всего блоков:          %u", pmm_total_blocks);
    com1_log("Адресс битовой карты:  %x", pmm_bitmap);
    com1_log("Размер карты:          %u", pmm_bitmap_size);
    com1_log("Начало памяти:         %x", pmm_mem_start);

    for(uint32_t i = 0; i < pmm_bitmap_size; i++) {
        if(pmm_bitmap[i] != 0) {
            com1_log("Память содержит мусор! %u", i);
        }
    }

    return pmm_test();
}



/**
 * @brief Поиск свободного блока физической памяти
 * 
 * @return uint32_t Номер блока
 */
uint32_t pmm_find_free_block() {
    uint32_t i;
    for(i = 0; i < pmm_total_blocks; i++) {
        if(!ISSET(i)) {
            return i;
        }
    }

    com1_log("Нехватка памяти!");

    return (uint32_t) -1;
}