#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* Hardware text mode color constants. */
enum vgaColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

struct kString {
	char *buffer;
	int length;
};

uint8_t vgaEntryColor(enum vgaColor fg, enum vgaColor bg);
uint16_t vgaEntry(unsigned char uc, uint8_t color);


void terminalWriteString(const char* data);
void terminalWrite(const char* data, size_t size);
void terminalPutChar(char c);
void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y);
void writeStringToSerial(char *str, int len);

void outputInitialize(void);
int isTransmitEmpty();
void writeSerial(char a);
void initSerial();