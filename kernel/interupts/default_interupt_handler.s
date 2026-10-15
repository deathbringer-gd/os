.section .text

.global default_interupt_handler
.type default_interupt_handler, @function

default_interrupt_handler:
    cli

1:
    hlt
    jmp 1b

.size default_interupt_handler, . - default_interupt_handler