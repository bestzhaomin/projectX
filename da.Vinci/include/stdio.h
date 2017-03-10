#ifndef _STDIO_H_
#define _STDIO_H_
#endif

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* 只能在32位 x86平台工作 */
#if !defined(__i386__)
#error "This obj needs to be compiled with a ix86-elf compiler"
#endif

/* 硬件文字模式颜色合集 */
enum vga_color {
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

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

/*计算字符串的长度*/
size_t strlen(const char* str);

static const size_t VGA_WIDTH = 80; //终端的宽度
static const size_t VGA_HEIGHT = 25; //终端的长度

size_t terminal_row; //终端当前行数
size_t terminal_column; //终端当前列数
uint8_t terminal_color; //终端颜色
uint16_t* terminal_buffer; //显卡内存地址

/*显示终端初始化*/
void terminal_initialize(void);

/*设置显示终端的颜色*/
void terminal_setcolor(uint8_t color);

/*在坐标(x,y)处显示字符c*/
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

/*显示字符c*/
void terminal_putchar(char c);

/*向终端写入一个长度为size的字符串*/
void terminal_write(const char* data, size_t size);

/*向终断写入字符串*/
void terminal_writestring(const char* data);




