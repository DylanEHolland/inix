PREKERNEL_SOURCES=$(wildcard prekernel/*.c)
TARGET_ARCH="i686-elf"
AS=$(TARGET_ARCH)-as


all:
	@-echo make build_prekernel

build_prekernel:
	@-$(AS) prekernel/boot.s -o objs/boot.o;