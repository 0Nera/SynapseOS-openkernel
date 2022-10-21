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
 * @brief Ошибка при делении на ноль
 * 
 */
static noreturn void division_by_zero() {
	com1_log("[ERROR]Division by zero");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Неверный код операции
 * 
 */
static noreturn void invalid_opcode() {
	com1_log("[ERROR]Invalid opcode");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Двойная ошибка(при прерывании или обработке ошибки)
 * 
 */
static noreturn void double_error() {
	com1_log("[ERROR]Double error");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Недопустимое исключение TSS
 * 
 */
static noreturn void invalid_tss() {
	com1_log("[ERROR]Invalid tss");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Сегмент недоступен
 * 
 */
static noreturn void segment_not_available() {
	com1_log("[ERROR]Segment not available");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Ошибка стека
 * 
 */
static noreturn void stack_error() {
	com1_log("[ERROR]Stack error");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Общая ошибка защиты
 * 
 */
static noreturn void general_protection_error() {
	com1_log("[ERROR]GPT error");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Ошибка страницы
 * 
 */
static noreturn void page_fault() {
	com1_log("[ERROR]Page fault");
	
	for(;;) {
		halt();
	}
}


/**
 * @brief Инициализации глобальной таблицы дескрипторов
 * 
 */
void gdt_init() {

}


/**
 * @brief Инициализация таблицы векторов прерываний
 * 
 */
void idt_init() {

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


    // Установка векторов прерываний для ошибок
	int_set_handler(0,  &division_by_zero);
	int_set_handler(6,  &invalid_opcode);
	int_set_handler(8,  &double_error);
	int_set_handler(10, &invalid_tss);
	int_set_handler(11, &segment_not_available);
	int_set_handler(12, &stack_error);
	int_set_handler(13, &general_protection_error);
	int_set_handler(14, &page_fault);
	int_set_handler(36, NULL);

	return true;
}