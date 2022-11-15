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
#include <int.h>
#include <dt.h>
#include <com1_log.h>



/**
 * @brief Загрузка регистра GDT 
 * 
 */
extern void gdt_flush(uint32_t);


/**
 * @brief Глобальная таблица дескрипторов
 * 
 */
gdt_entry_t    gdt_entries[5];


/**
 * @brief Структура указателей на GDT 
 * 
 */
gdt_ptr_t      gdt_ptr;


/**
 * @brief Таблица дескрипторов прерываний
 * 
 */
idt_entry_t  idt_entries[256];


/**
 * @brief Структура указателей размещения IDT
 * 
 */
idt_ptr_t    idt_ptr;


/**
 * @brief Загрузка рагистра IDTR - внешняя ассемблерная функция
 * 
 */
extern void idt_flush(uint32_t);


/**
 * @brief Основной обработчик прерываний
 * 
 */
extern void int_common_stub();

static void idt_init();
static void gdt_init();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);


/**
 * @brief Установка значения в таблицу GDT
 * 
 * @param num Номер сегмента
 * @param base База сегмента
 * @param limit Лимит сегмента
 * @param access Байт доступа
 * @param gran Байт гранулярности
 */
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)    {
    /* Заполняем поля базы */
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    /* Заполняем поля лимита */
    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0xF;

    /* Заполняем байты доступа и гранулярности */
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;   
}


/**
 * @brief Инициализации глобальной таблицы дескрипторов
 * 
 */
void gdt_init() {
    com1_log("[GDT]");
    /* Определяем размер GDT */
    gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
    /* Вычисляем адрес размещения GDT в памяти*/
    gdt_ptr.base = (uint32_t) &gdt_entries;
        
    /* Нулевой дескриптор */
    gdt_set_gate(0, 0, 0, 0, 0);   
    /* Дескриптор кода ядра  (ring 0)*/
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    /* Дескриптор данных ядра (ring 0)*/  
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    /* Дескриптор кода пользовательского режима (ring 3)*/ 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    /* Дескриптор данных пользовательского режима (ring 3)*/  
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   

    /* Включаем сегментную адресацию  */
    gdt_flush((uint32_t)&gdt_ptr);

    com1_log_dump((uint32_t*)gdt_entries, 40);
}


/**
 * @brief  Установка значения в таблицу IDT
 * 
 * @param num Номер прерывания
 * @param base Адресс обработчика
 * @param selector Селектор сегмента ядра
 * @param flags Флаги доступа
 */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    
    idt_entries[num].selector = selector;
    idt_entries[num].allways0 = 0;

    idt_entries[num].flags = flags; /* | 0x60 - для пользовательского */
                                    /* режима */ ;
}



/**
 * @brief Инициализация таблицы векторов прерываний
 * 
 */
void idt_init() {
    com1_log("[IDT]");
    /* Инициализация структуры указателя размером и адресом IDT */
    idt_ptr.limit = sizeof(idt_entry_t)*256 - 1;
    idt_ptr.base = (uint32_t) &idt_entries;
    
    /* Очистка памяти */
    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);   

    /* Инициализация обоих PIC */
    ports_outb(0x20, PIC1_ICW1); /* ICW1 */
    ports_outb(0xA0, PIC2_ICW1);

    ports_outb(0x21, PIC1_ICW2); /* ICW2 */
    ports_outb(0xA1, PIC2_ICW2);

    ports_outb(0x21, PIC1_ICW3); /* ICW3 */
    ports_outb(0xA1, PIC2_ICW3);

    ports_outb(0x21, PIC1_ICW4); /* ICW4 */
    ports_outb(0xA1, PIC2_ICW4);
    
    /* Разрешаем прерывания на всех линиях */
    ports_outb(0x21, 0x00);      /* OCW1 */
    ports_outb(0xA1, 0x00);

}


/**
 * @brief Инициализация таблиц дескрипторов 
 * 
 * @return true В случае успешной настройки
 * @return false В случае ошибки
 */
bool dt_init() {
    gdt_init();
    idt_init();
    int_init();

    /* Загрузка регистра IDTR */
    idt_flush((uint32_t)&idt_ptr);
    com1_log_dump(&idt_ptr, sizeof(idt_ptr));
    
    return true;
}