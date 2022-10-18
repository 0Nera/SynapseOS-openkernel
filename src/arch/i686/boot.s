/**
 * @file boot.s
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief Подзагрузчик ядра
 * @version 0.1.0
 * @date 18-10-2022
 * 
 * @copyright Арен Елчинян (c) 2022
 * 
 */


# Использованы материалы
# https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html


# 32х битный код
.code32

# Размер стека
# 4096 * 16 * 8 = 524288 байт. 
# 524288 байт = 512 килобайт
.set STACK_SIZE, 4096 * 16 * 8
# Multiboot2 теги
.set TAG_END,          0
.set TAG_FRAMEBUFFER,  5

# Multiboot2 флаги
.set TAG_REQUIRED,     0
.set TAG_OPTIONAL,     1

# Multiboot2 константы
.set MAGIC,            0xE85250D6
.set ARCH,             0
.set HEADER_LEN,       (multiboot_end - multiboot_start)
.set CHECKSUM,         -(MAGIC + ARCH + HEADER_LEN)

.set KERNEL_VIRTUAL_BASE, 0xC0000000
.set KERNEL_PAGE_NUMBER,  (KERNEL_VIRTUAL_BASE >> 22)

# Объявляем мультизагрузочный заголовок, который помечает программу как ядро.
# Это магические значения, которые задокументированы в стандарте мультизагрузки.
# Загрузчик будет искать этот заголовок в первых 8 килобайтах файла ядра, выровненного по 32-битной границе.
# Подпись находится в отдельном разделе, поэтому заголовок можно принудительно разместить в первых 8 килобайтах файла ядра.
.section .multiboot
multiboot_start:
    # Magic
    .align 8
    .long MAGIC
    .long ARCH
    .long HEADER_LEN
    .long CHECKSUM

    # Графические флаги
    /*
    .align 8
    .short TAG_FRAMEBUFFER
    .short TAG_REQUIRED
    .long 20
    .long 1024
    .long 768
    .long 32
*/
    # Конец тега
    .align 8
    .short TAG_END
    .short TAG_REQUIRED
    .long 8
multiboot_end:

.section	.text
.global _start

# Входная точка
_start:
	cli
	mov 	$(_stack + STACK_SIZE), %esp
	push    $0x0
	popf
	push	%esp
	push	%ebx
	push	%eax
	call	kernel_startup
	hlt

# Останавливаем процессор	
__halt_me:
	cli
        hlt
	jmp	__halt_me

.comm _stack, STACK_SIZE
