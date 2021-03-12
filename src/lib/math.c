#include "math.h"
#include "printf.h"

double sin(double angle) {
    //printf("Starting angle: %d\n", (int) (angle * 10000));
    int multiplier = 1;
    if (angle < 0) {
        //printf("Changing multiplier\n");
        multiplier = -1;
        angle *= -1;
    }
    angle -= ((int) (angle / (2 * PI))) * (2 * PI);
    //printf("New angle: %d\n", (int) (angle * 10000));
    
    // angle is now between 0 and 2PI

    if (angle > PI) {
        angle -= 2 * PI;
    }

    //printf("New angle: %d\n", (int) (angle * 10000));
    // angle is now between -PI and PI

    if (angle > PI/2) {
        angle -= 2 * (angle - PI/2);
    } else if (angle < -PI/2) {
        angle += 2 * (-PI/2 - angle);
    }

    // angle is now between -PI/2 and PI/2
    //printf("After converting angle: %d\n", (int) (angle * 10000));

    double result = 0;

    // Taylor series
    for (int i = 1; i <= 7; i += 2) {
        double curr_iteration_result = 1;
        for (int k = 1; k <= i; k++) {
            curr_iteration_result *= angle;
            curr_iteration_result /= k;
        }
        if (i % 4 == 1) result += curr_iteration_result;
        else result -= curr_iteration_result;
    }

    return multiplier * result;
}

double sqrt(double x) {
    return 0;
}
