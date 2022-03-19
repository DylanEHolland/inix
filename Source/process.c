#include <process.h>
#include <terminal.h>

void initProcessManager() {
    terminalWriteString("Starting process manager...");
}

void spawnProcessZero() {

}

void runProcess(struct process *proc) {
    terminalWriteString("Starting process...");
    terminalPutChar((char)proc->id);
    // proc->bytes;
}