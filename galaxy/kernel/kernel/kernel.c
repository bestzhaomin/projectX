#include <stdio.h>

#include <kernel/tty.h>

/* 内核入口
 * 现在只是打印文字
 */
void kernel_main(void)
{
    terminal_initialize();
    for (int i = 0; i < 10; i++)
		printf("I'm DaVici,row=%d\n", i);
}
