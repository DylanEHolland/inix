#include <terminal.h>
#include <string.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "Only 32bit is supported at this time"
#endif

void kernel_main() {
    output_initialize();
    terminal_writestring("Welcome inix 0.0.0.0.0.0.0.1");
}