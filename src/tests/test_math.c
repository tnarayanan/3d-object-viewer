#include "math.h"
#include "uart.h"
#include "printf.h"

void test_trig(void) {
    for (float theta = -2*PI; theta <= 2*PI + 2; theta += PI/4) {
        int angle = theta * 10000;
        int result = sin(theta) * 10000;
        int dec_part = result % 10000;
        result /= 10000;
        printf("sin(%d) = %d.%d\n", angle, result, dec_part);
    }

    double x = PI/2 + 6*PI;
    printf("sin(%d) = %d\n", (int) (x * 10000), (int) (sin(x) * 10000));
    printf("cos(%d) = %d\n", (int) (x * 10000), (int) (cos(x) * 10000));
}

void test_sqrt(void) {
    double x = 64;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));

    x = 81;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));

    x = 0;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));

    x = 37;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));

    x = 91.45;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));

    x = 9123.563;
    printf("sqrt(%d) = %d\n", (int) (x * 10000), (int) (sqrt(x) * 10000));
}

void main(void) {
    printf("Running math library tests...\n");
    test_trig();
    test_sqrt();
    printf("Finished running math library tests\n");
    uart_putchar(EOT);
}
