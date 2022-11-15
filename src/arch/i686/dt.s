.global    gdt_flush
.global    idt_flush

.extern isr_handler

gdt_flush:

/* Загружаем регистр GDTR */
    mov     4(%esp), %eax /* Берем из стека переданный указатель */
    lgdt    (%eax) /* Загружаем этим указателем GDTR */
/* Загрузка всех селекторов сегментов данных */   
    mov    $0x10, %ax
    mov    %ax, %ds
    mov    %ax, %es
    mov    %ax, %fs
    mov    %ax, %gs
    mov    %ax, %ss
/* Косвенно загружаем селектор сегмента кода CS */
/* осуществляя длинный переход */   
    ljmp    $0x08,$flush
flush:
    ret



idt_flush:
/* Загрузка IDTR указателем полученным из стека */
/* переданным в качестве параметра */
    mov    4(%esp), %eax /* берем параметр из стека */
    lidt    (%eax)   /* загружаем регистр IDTR */
    ret

