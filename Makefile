PREKERNEL_SOURCES=$(wildcard Source/*.c)
LIB_SOURCES=$(wildcard Library/*.c)
TARGET_ARCH="i686-elf"
AS=$(TARGET_ARCH)-as
CC=$(TARGET_ARCH)-gcc -std=c17


all: build

build_lib: obj_dir
	@-for f in $(LIB_SOURCES); do \
		OBJ_NAME=Build/`echo $$f | cut -d . -f 1 | cut -d / -f 2`.o && \
		$(CC) -c $$f -o $$OBJ_NAME -I./Library -std=c17 -ffreestanding -O2 -Wall -Wextra; \
	done;

build: build_lib
	@-$(AS) Source/boot.S -o Build/boot.o;
	@-for f in $(PREKERNEL_SOURCES); do \
		OBJ_NAME=Build/`echo $$f | cut -d . -f 1 | cut -d / -f 2`.o && \
		$(CC) -c $$f -o $$OBJ_NAME -I./Library -std=c17 -ffreestanding -O2 -Wall -Wextra; \
	done;
	@-$(CC) -T Source/linker.ld -o Build/prekernel.bin -ffreestanding -O2 -nostdlib build/*.o -lgcc;

clean:
	@-rm Build/*.o &>/dev/null || exit 0;
	@-rm Build/*.bin &>/dev/null || exit 0;
	@-echo "Cleaned"

obj_dir:
	@-[ ! -d Build ] && mkdir -p Build || exit 0;

run:
	@-qemu-system-x86_64 -kernel build/prekernel.bin -serial stdio; 