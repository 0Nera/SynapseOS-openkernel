.code32

.set INIT_MULTIBOOT_HEADER_MAGIC,           0x1BADB002
.set INIT_MULTIBOOT_HEADER_FLAGS,           0x00000001
.set INIT_MULTIBOOT_CHECKSUM,               0x00000000 - (INIT_MULTIBOOT_HEADER_MAGIC + INIT_MULTIBOOT_HEADER_FLAGS)

# 4096 * 16 * 8 = 524288 байт. 
# 524288 байт = 512 килобайт
.set STACK_SIZE, 4096 * 16 * 8
# Объявляем мультизагрузочный заголовок, который помечает программу как ядро.
# Это магические значения, которые задокументированы в стандарте мультизагрузки.
# Загрузчик будет искать этот заголовок в первых 8 килобайтах файла ядра, выровненного по 32-битной границе.
# Подпись находится в отдельном разделе, поэтому заголовок можно принудительно разместить в первых 8 килобайтах файла ядра.
.section .multiboot
.align 4

.int INIT_MULTIBOOT_HEADER_MAGIC
.int INIT_MULTIBOOT_HEADER_FLAGS
.int INIT_MULTIBOOT_CHECKSUM

/*
.long MAGIC
.long FLAGS
.long CHECKSUM          # Контрольная сумма
*/
# .long 0, 0, 0, 0, 0     # Неиспользуется
# .long 0                 # 0 - графический режим
# .long 1024, 768, 32     # Ширина, длина, глубина

.section	.text
.global _start

_start:
	cli
	mov 	$(_stack + STACK_SIZE), %esp
	push $0x0
	popf
	push	%esp
	push	%ebx
	push	%eax
	call	kernel_startup
	hlt
		
loop: /* loop infinity */ 
		jmp	loop

.comm _stack, STACK_SIZE
