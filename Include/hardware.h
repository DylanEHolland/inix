#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);

#endif