/**
 * @file ports.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 19-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


#include <libk.h>


#ifndef	_PORTS_H
#define	_PORTS_H	1


#if (defined __i386__ || defined __x86_64__)

#define PORTS_COM1 0x3f8
#define PORTS_COM2 0x2F8
#define PORTS_COM3 0x3E8
#define PORTS_COM4 0x2E8
#define PORTS_COM5 0x5F8
#define PORTS_COM6 0x4F8
#define PORTS_COM7 0x5E8
#define PORTS_COM8 0x4E8

#define PORTS_PIC1 0x20
#define PORTS_PIC2 0xA0
#define PORTS_ICW1 0x11
#define PORTS_ICW4 0x01
#define PORTS_PIC1 0x20		// Стандартный IO адрес главного PIC
#define PORTS_PIC2 0xA0		// Стандартный IO адрес вторичного PIC
#define PORTS_PIC1_COMMAND	PORTS_PIC1
#define PORTS_PIC1_DATA	(PORTS_PIC1 + 1)
#define PORTS_PIC2_COMMAND	PORTS_PIC2
#define PORTS_PIC2_DATA	(PORTS_PIC2 + 1)

uint8_t  ports_inb(uint16_t port);                // Чтение 1 байта из порта
uint16_t ports_inw(uint16_t port);                // Чтение 2 байт из порта
uint32_t ports_inl(uint16_t port);                // Чтение 4 байт из порта
void     ports_outb(uint16_t port, uint8_t  val); // Отправка 1 байта в порт
void     ports_outw(uint16_t port, uint16_t val); // Отправка 2 байта в порт
void     ports_outl(uint16_t port, uint32_t val); // Отправка 4 байта в порт

#endif 


#endif // ports.h