#include <terminal.h>
#include <string.h>
#include <hardware.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer;

void terminalWriteString(const char* data) 
{
	terminalWrite(data, strlen(data));
	writeStringToSerial((char *)data, strlen(data));
}

void terminalSetColor(uint8_t color) 
{
	terminalColor = color;
}
 
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminalBuffer[index] = vgaEntry(c, color);
}
 
void terminalPutChar(char c) 
{
	terminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);
	if (++terminalColumn == VGA_WIDTH) {
		terminalColumn = 0;
		if (++terminalRow == VGA_HEIGHT)
			terminalRow = 0;
	}
}
 
void terminalWrite(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		terminalPutChar(data[i]);
	}
}
 
uint8_t vgaEntryColor(enum vgaColor fg, enum vgaColor bg) 
{
	return fg | bg << 4;
}

uint16_t vgaEntry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
 

void outputInitialize(void) 
{
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = vgaEntryColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminalBuffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminalBuffer[index] = \
				vgaEntry(' ', terminalColor);
		}
	}
}

#define PORT 0x3f8          // COM1
 
void initSerial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
   outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)
 
   // Check if serial is faulty (i.e: not same byte as sent)
//    if(inb(PORT + 0) != 0xAE) {
//       return 1;
//    }
 
   // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(PORT + 4, 0x0F);
}

int isTransmitEmpty() {
   return inb(PORT + 5) & 0x20;
}
 
void writeSerial(char a) {
   while (isTransmitEmpty() == 0);
 
   outb(PORT,a);
}

void writeStringToSerial(char *str, int len) {
	for(int i = 0; i < len; i++) {
		writeSerial(str[i]);
	}
}