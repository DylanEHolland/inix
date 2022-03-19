#include <terminal.h>
#include <string.h>
#include <process.h>
#include <messages.h>

void kernel_main() {
    outputInitialize();
    initProcessManager();
}