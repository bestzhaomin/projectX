#include <stdio.h>

#include <kernel/tty.h>

/* 内核入口
 * 现在只是打印文字
 */
void kernel_main(void) {
	terminal_initialize();
	int i = 49;
	printf("Hello, I'm Da.Vinci!\n");
	printf("Hello, I'm %d Galaxy123!\n",i);
}
