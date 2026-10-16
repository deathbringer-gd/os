KERNEL := build/os.bin

C_SRCS := $(shell find kernel -name '*.c')
ASM_SRCS := $(shell find boot kernel -name '*.s')

OBJS := \
	$(C_SRCS:%.c=build/%.o) \
	$(ASM_SRCS:%.s=build/%.o)

CC := gcc
AS := as

ARCH := -m32 -fno-pie -no-pie -fno-stack-protector

CFLAGS := $(ARCH) \
	-std=gnu11 \
	-ffreestanding \
	-fno-builtin \
	-O2 \
	-Wall \
	-Wextra \
	-Ikernel \
	-Ikernel/terminal \
	-Ikernel/drivers \
	-Ikernel/interupts \
	-MMD \
	-MP

ASFLAGS := --32

LDFLAGS := $(ARCH) \
	-T linker.ld \
	-ffreestanding \
	-nostdlib \
	-Wl,--build-id=none

.PHONY: all clean run check

all: $(KERNEL)

$(KERNEL): $(OBJS) linker.ld
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

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

clean:
	rm -rf build

-include $(OBJS:.o=.d)