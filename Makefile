PREKERNEL_SOURCES=$(wildcard prekernel/*.c)
LIB_SOURCES=$(wildcard lib/*.c)
TARGET_ARCH="i686-elf"
AS=$(TARGET_ARCH)-as
CC=$(TARGET_ARCH)-gcc


all:
	@-echo make build_prekernel

build_lib:
	@-for f in $(LIB_SOURCES); do \
		OBJ_NAME=objs/`echo $$f | cut -d . -f 1 | cut -d / -f 2`.o && \
		$(CC) -c $$f -o $$OBJ_NAME -I./lib -std=c17 -ffreestanding -O2 -Wall -Wextra; \
	done;

build_prekernel: build_lib
	@-$(AS) prekernel/boot.s -o objs/boot.o;
	@-for f in $(PREKERNEL_SOURCES); do \
		OBJ_NAME=objs/`echo $$f | cut -d . -f 1 | cut -d / -f 2`.o && \
		$(CC) -c $$f -o $$OBJ_NAME -I./lib -std=c17 -ffreestanding -O2 -Wall -Wextra; \
	done;
	@-$(CC) -T prekernel/linker.ld -o objs/prekernel.bin -ffreestanding -O2 -nostdlib objs/*.o -lgcc;

run:
	`mdfind qemu-system-x86_64 | head -n 1` -kernel objs/prekernel.bin;

clean:
	rm objs/*.o;
	rm objs/*.bin;