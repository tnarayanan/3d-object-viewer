#include "printf.h"
#include "uart.h"

void main(void)
{
    uart_init();
    printf("Running tests from file %s\n", __FILE__);
    uart_putchar(EOT);
}
