#include <terminal.h>
#include <string.h>
#include <process.h>

void kernel_main() {
    outputInitialize();
    initProcessManager();
}