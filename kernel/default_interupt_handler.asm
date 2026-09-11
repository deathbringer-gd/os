global default_interupt_handler

default_interupt_handler:
    cli
    hlt
    jmp default_interupt_handler