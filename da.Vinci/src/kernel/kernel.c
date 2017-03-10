#include "../../include/stdio.h"

void kernel_main(void) {
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, I'm called da.Vinci, the computer designed by Zhaomin.");
}

