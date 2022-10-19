/**
 * @file ports.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Прослойка для работы с портами ввода-вывода
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>


/**
 * @brief Получение одного байта из порта
 * 
 * @param port Порт
 * @return uint8_t Значение из порта
 */
uint8_t ports_inb(uint16_t port) {
	uint8_t ret;
	asm volatile( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}


/**
 * @brief Получение 2 байт(word) из порта 
 * 
 * @param port Порт
 * @return uint16_t Значение из порта
 */
uint16_t ports_inw(uint16_t port) {
	uint16_t ret;
	asm volatile( "inw %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}


/**
 * @brief Получение 4 байт из порта
 * 
 * @param port Порт
 * @return uint32_t Значение из порта
 */
uint32_t ports_inl(uint16_t port) {
	uint32_t ret;
	asm volatile( "inl %1, %0" : "=a"(ret) : "Nd"(port) );
	return ret;
}


/**
 * @brief Ввод одного байта в порт
 * 
 * @param port Порт
 * @param val Входные данные
 */
void ports_outb(uint16_t port, uint8_t  val) {
	asm volatile( "outb %0, %1" : : "a"(val), "Nd"(port) );
}


/**
 * @brief Ввод 2 байт (word) в порт
 * 
 * @param port Порт
 * @param val Входные данные
 */
void ports_outw(uint16_t port, uint16_t val) {
	asm volatile( "outw %0, %1" : : "a"(val), "Nd"(port) );
}


/**
 * @brief Ввод 4 байт в порт
 * 
 * @param port Порт
 * @param val  Входные данные
 */
void ports_outl(uint16_t port, uint32_t val) {
	asm volatile( "outl %0, %1" : : "a"(val), "Nd"(port) );
}