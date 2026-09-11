# Build the 32-bit Multiboot kernel.
#
#   make          build build/os.bin
#   make run      boot the kernel in QEMU
#   make check    confirm the kernel has a valid Multiboot header
#   make iso      build a bootable GRUB ISO (needs grub-pc-bin and xorriso)
#   make clean    delete all build output

KERNEL := build/os.bin
ISO    := build/os.iso

# Use an i686-elf cross-compiler if one is installed (or pass CROSS=prefix-),
# otherwise fall back to the host toolchain in 32-bit mode.
ifeq ($(origin CROSS),undefined)
CROSS := $(if $(shell command -v i686-elf-gcc 2>/dev/null),i686-elf-)
endif

ifneq ($(CROSS),)
CC      := $(CROSS)gcc
AS      := $(CROSS)as
ARCH    :=
ASFLAGS :=
LIBS    := -lgcc
else
CC      := gcc
AS      := as
ARCH    := -m32 -fno-pie -no-pie -fno-stack-protector
ASFLAGS := --32
LIBS    :=
endif

CFLAGS  := $(ARCH) -std=gnu11 -ffreestanding -O2 -Wall -Wextra -Ikernel -MMD -MP
LDFLAGS := $(ARCH) -T linker.ld -ffreestanding -nostdlib -Wl,--build-id=none

C_SRCS   := $(wildcard kernel/*.c)
ASM_SRCS := $(wildcard boot/*.s)
OBJS     := $(ASM_SRCS:%.s=build/%.o) $(C_SRCS:%.c=build/%.o)

.PHONY: all run check iso clean

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

run: $(KERNEL)
	qemu-system-i386 -kernel $<

check: $(KERNEL)
	grub-file --is-x86-multiboot $<
	@echo "$< is a valid Multiboot kernel"

iso: $(ISO)

$(ISO): $(KERNEL)
	@mkdir -p build/isodir/boot/grub
	cp $< build/isodir/boot/os.bin
	printf 'menuentry "os" {\n\tmultiboot /boot/os.bin\n}\n' > build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ build/isodir

clean:
	rm -rf build

-include $(OBJS:.o=.d)
