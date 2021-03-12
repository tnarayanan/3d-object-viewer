#include "vector_math.h"
#include "uart.h"
#include "printf.h"
#include "assert.h"

void print_vector(const char *pref, point_t p) {
    printf("%s {%d, %d, %d}\n", pref, (int) (p.x * 10000), (int) (p.y * 10000), (int) (p.z * 10000));
}

void test_vector_add_sub(void) {
    point_t a = {1, 2, 3};
    point_t b = {4, 5, 6};
    
    point_t a_plus_b = vector_add(a, b);
    point_t expected_1 = {5, 7, 9};
    print_vector("a + b:   ", a_plus_b);
    print_vector("Expected:", expected_1);

    point_t c = {-1, 12, 7};
    point_t d = {1, -15, -6};
    
    point_t c_plus_d = vector_add(c, d);
    point_t expected_2 = {0, -3, 1};
    print_vector("c + d:   ", c_plus_d);
    print_vector("Expected:", expected_2);
}

void test_vector_scalar_mul(void) {
    point_t a = {1, 2, 3};
    double k = 3;
    
    point_t a_times_k = vector_scalar_mul(a, k);
    point_t expected_1 = {3, 6, 9};
    print_vector("3a:      ", a_times_k);
    print_vector("Expected:", expected_1);

    point_t b = {1, -15, -6};
    k = 0.75;
    
    point_t b_times_k = vector_scalar_mul(b, k);
    point_t expected_2 = {0.75, -11.25, -4.5};
    print_vector("0.75b:   ", b_times_k);
    print_vector("Expected:", expected_2);

    point_t c = {-1, 12, 7};
    k = -0.472;
    
    point_t c_times_k = vector_scalar_mul(c, k);
    point_t expected_3 = {0.472, -5.664, -3.304};
    print_vector("-0.472c: ", c_times_k);
    print_vector("Expected:", expected_3);

    point_t d = {-1, 12, 7};
    k = 0;
    
    point_t d_times_k = vector_scalar_mul(d, k);
    point_t expected_4 = {0, 0, 0};
    print_vector("0d:      ", d_times_k);
    print_vector("Expected:", expected_4);
}

void test_vector_cross_product(void) {
    point_t a = {2, 3, 4};
    point_t b = {5, 6, 7};

    point_t a_cross_b = vector_cross_product(a, b);
    point_t expected_1 = {-3, 6, -3};
    print_vector("a x b:   ", a_cross_b);
    print_vector("Expected:", expected_1);

    point_t c = {3, -3, 1};
    point_t d = {4, 9, 2};

    point_t c_cross_d = vector_cross_product(c, d);
    point_t expected_2 = {-15, -2, 39};
    print_vector("c x d:   ", c_cross_d);
    print_vector("Expected:", expected_2);
}

void test_vector_dot_product(void) {
    point_t a = {2, 3, 4};
    point_t b = {5, 6, 7};

    double a_dot_b = vector_dot_product(a, b);
    double expected_1 = 56;
    printf("a dot b:  %d\n", (int) (a_dot_b * 10000));
    printf("Expected: %d\n", (int) (expected_1 * 10000));

    point_t c = {2.52, 7.12, -14.934};
    point_t d = {-5.912, 0.453, 9.182};

    double c_dot_d = vector_dot_product(c, d);
    double expected_2 = -148.796868;
    printf("c dot d:  %d\n", (int) (c_dot_d * 10000));
    printf("Expected: %d\n", (int) (expected_2 * 10000));
}

void test_vector_projection(void) {
    point_t a = {1, 4, 0};
    point_t b = {4, 2, 4};

    point_t a_proj_b = vector_projection(a, b);
    point_t expected_1 = {4.0/3.0, 2.0/3.0, 4.0/3.0};
    print_vector("a proj b:", a_proj_b);
    print_vector("Expected:", expected_1);
}

void main(void) {
    printf("Running vector math library tests...\n");

    test_vector_add_sub();
    test_vector_scalar_mul(); 
    test_vector_cross_product();
    test_vector_dot_product();
    test_vector_projection();

    printf("Finished running vector math library tests\n");
    uart_putchar(EOT);
}
