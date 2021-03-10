#include "uart.h"
#include "printf.h"
#include "assert.h"
#include "ff.h"

FATFS fs;

void test_read_file(void) {
    FIL fil;
    FRESULT fr;
    char line[100];

    fr = f_open(&fil, "message.txt", FA_READ);
    assert(!fr);

    unsigned int bytes_read = 0;
    f_read(&fil, line, 100, &bytes_read);

    for (int i = 0; i < bytes_read; i++)
        printf("%c", line[i]);

    printf("\n");
    printf("Total bytes read: %d\n", bytes_read);

    f_close(&fil);
}

void main(void) {
    f_mount(&fs, "", 0);

    test_read_file();
    uart_putchar(EOT);
}
