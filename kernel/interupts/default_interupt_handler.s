.section .text

.global default_interrupt_handler
.type default_interrupt_handler, @function

default_interrupt_handler:
    cli

1:
    hlt
    jmp 1b

.size default_interrupt_handler, . - default_interrupt_handler