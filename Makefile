KERNEL := build/os.bin
ISO    := build/os.iso

CROSS ?= i686-elf-

CC := $(CROSS)gcc
AS := $(CROSS)as

CFLAGS := \
	-std=gnu11 \
	-ffreestanding \
	-fno-builtin \
	-fno-stack-protector \
	-O2 \
	-Wall \
	-Wextra \
	-Ikernel \
	-Ikernel/terminal \
	-Ikernel/drivers \
	-Ikernel/interupts \
	-MMD \
	-MP

ASFLAGS :=

LDFLAGS := \
	-T linker.ld \
	-ffreestanding \
	-nostdlib \
	-Wl,--build-id=none

C_SRCS := $(shell find kernel -name '*.c')
ASM_SRCS := $(shell find boot kernel -name '*.s')

OBJS := \
	$(patsubst %.c,build/%.o,$(C_SRCS)) \
	$(patsubst %.s,build/%.o,$(ASM_SRCS))

.PHONY: all run check-multiboot iso clean

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgcc

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

check-multiboot: $(KERNEL)
	grub-file --is-x86-multiboot $(KERNEL)
	@echo "$(KERNEL) is a valid Multiboot kernel"

run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

iso: $(ISO)

$(ISO): $(KERNEL)
	@mkdir -p build/isodir/boot/grub
	cp $(KERNEL) build/isodir/boot/os.bin
	printf 'menuentry "os" {\n\tmultiboot /boot/os.bin\n}\n' > build/isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ build/isodir

clean:
	rm -rf build

-include $(OBJS:.o=.d)
	