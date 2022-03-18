#include <terminal.h>
#include <string.h>

void kernel_main() {
    output_initialize();
    terminal_writestring("Welcome to inix");
}