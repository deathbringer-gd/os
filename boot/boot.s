// set startup flags
.set ALIGN, 1<<0
.set MEMINFO, 1<<1
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

// put startup flags in memory
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

// allign correctly and define stack
.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

// define start function
.section .text
.global _start
.type _start, @function
_start:

// set stack and call kernel
mov $stack_top, %esp
call kernel_main
cli
1: hlt
jmp 1b

.size _start, . - _start