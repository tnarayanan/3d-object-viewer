#include "gpu_programs.h"
#include "uart.h"
#include "printf.h"
#include "timer.h"

void test_peek_poke(void) {
    char program_peek[4] = {
        0x00, 0x08, // ld r0, (r0)
        0x5a, 0x00, // rts
    };
    char program_poke[4] = {
        0x01, 0x09, // st r1, (r0)
        0x5a, 0x00, // rts
    };
    gpu_program_add("peek", program_peek, 4);
    gpu_program_add("poke", program_poke, 4);

    unsigned int addr = 0x7e200008;

    unsigned int initial_val = gpu_program_run("peek", addr, 0, 0, 0, 0, 0);
    printf("Peek at %08x before poke: %d\n", addr, initial_val);

    int poke_val = 17;
    gpu_program_run("poke", addr, poke_val, 0, 0, 0, 0);
    printf("Poked %d into %08x\n", poke_val, addr);

    unsigned int new_val = gpu_program_run("peek", addr, 0, 0, 0, 0, 0);
    printf("Peek at %08x after poke:  %d\n", addr, new_val);
}

void test_gpio_on_off(void) {
    // assembly code to config, set, and clear gpio 20
    char program_config[14] = {
        0x01, 0xe8, 0x08, 0x00, 0x20, 0x7e, // movi r1, 0x7e200008
        0x10, 0x08, // ld r0, (r1)
        0x10, 0x60, // movi r0, 1
        0x10, 0x09, // st r0, (r1)
        0x5a, 0x00, // rts
    };
    char program_set[16] = {
        0x01, 0xe8, 0x1c, 0x00, 0x20, 0x7e, // movi r1, 0x7e20001c
        0x03, 0xe8, 0x00, 0x00, 0x10, 0x00, // movi r3, 1 << 20
        0x13, 0x09, // st r3, (r1)
        0x5a, 0x00, // rts
    };
    char program_clr[16] = {
        0x01, 0xe8, 0x28, 0x00, 0x20, 0x7e, // movi r1, 0x7e200028
        0x03, 0xe8, 0x00, 0x00, 0x10, 0x00, // movi r3, 1 << 20
        0x13, 0x09, // st r3, (r1)
        0x5a, 0x00, // rts
    };

    gpu_program_add("config20", program_config, 14);
    gpu_program_add("set20", program_set, 16);
    gpu_program_add("clr20", program_clr, 16);

    gpu_program_run_no_params("config20");
    for (int i = 0; i < 3; i++) {
        gpu_program_run_no_params("set20");
        printf("on\n");
        timer_delay(1);
        gpu_program_run_no_params("clr20");
        printf("off\n");
        timer_delay(1);
    }
}

void test_gpu_program_from_file(void) {
    gpu_program_add_from_file("gpu_blink", "gpu_blink.bin");
    printf("Running gpu_blink...\n");
    gpu_program_run_no_params("gpu_blink");
    printf("Finished running gpu_blink\n");
}

void main(void) {
    gpu_programs_init();

    test_peek_poke();
    //test_gpio_on_off();
    test_gpu_program_from_file();

    uart_putchar(EOT);
}
