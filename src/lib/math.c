#include "math.h"
#include "printf.h"
#include "assert.h"

float sin(float angle) {
    int multiplier = 1;
    if (angle < 0) {
        multiplier = -1;
        angle *= -1;
    }
    angle -= ((int) (angle / (2 * PI))) * (2 * PI);
    
    // angle is now between 0 and 2PI

    if (angle > PI) {
        angle -= 2 * PI;
    }

    // angle is now between -PI and PI

    if (angle > PI/2) {
        angle -= 2 * (angle - PI/2);
    } else if (angle < -PI/2) {
        angle += 2 * (-PI/2 - angle);
    }

    // angle is now between -PI/2 and PI/2

    float result = 0;

    // Taylor series
    for (int i = 1; i <= 7; i += 2) {
        float curr_iteration_result = 1;
        for (int k = 1; k <= i; k++) {
            curr_iteration_result *= angle;
            curr_iteration_result /= k;
        }
        if (i % 4 == 1) result += curr_iteration_result;
        else result -= curr_iteration_result;
    }

    return multiplier * result;
}

float sqrt(float x) {
    assert(x >= 0);

    float ans = x / 2;
    float tmp = 0;

    while (ans != tmp) {
        tmp = ans;
        ans = (x/tmp + tmp) / 2;
    }
    
    return ans;
}
