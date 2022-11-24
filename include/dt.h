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
#include <libk.h>


#ifndef    _DT_H
#define    _DT_H    1


#if (defined __i386__ || defined __x86_64__)


#define        PIC1_ICW1    0x11
#define        PIC1_ICW2    0x20
#define        PIC1_ICW3    0x04
#define        PIC1_ICW4    0x01

#define        PIC2_ICW1    0x11
#define        PIC2_ICW2    0x28
#define        PIC2_ICW3    0x02
#define        PIC2_ICW4    0x01


/**
 * @brief Запись глобальной таблицы дескрипторов (GDT)
 * 
 */
struct gdt_entry_struct {
    uint16_t    limit_low;   ///< Младшее слово лимита
    uint16_t    base_low;    ///< Младшее слово базы
    uint8_t     base_middle; ///< Средняя часть базы
    uint8_t     access;      ///< Байт доступа
    uint8_t     granularity; ///< Байт гранулярности
    uint8_t     base_high;   ///< Старшая часть базы
} PACKED;


/**
 * @brief Структура с указателями на GDT
 * 
 */
struct gdt_ptr_struct {
    uint16_t    limit;
    uint32_t    base;
} PACKED;


/**
 * @brief Запись в таблице дескрипторов прерываний (IDT)
 * 
 */
struct idt_entry_struct {
  uint16_t    base_low;  ///< Младшее слово адреса обработчика
  uint16_t    selector;  ///< Селектор сегмента ядра
  uint8_t     allways0;  ///< Всегда ноль
  uint8_t     flags;     ///< Байт флагов доступа
  uint16_t    base_high; ///< Старшее слово адреса обработчика
} PACKED;


/**
 * @brief Структура указателей размещения IDT
 * 
 */
struct idt_ptr_struct {
    uint16_t    limit; ///< Размер таблицы IDT
    uint32_t    base;  ///< Адрес первой записи IDT
} PACKED;

typedef struct gdt_entry_struct    gdt_entry_t;
typedef struct gdt_ptr_struct      gdt_ptr_t;

typedef struct idt_entry_struct    idt_entry_t;
typedef struct idt_ptr_struct      idt_ptr_t;


void init_descriptor_tables();
bool dt_init();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

#endif


#endif // dt.h