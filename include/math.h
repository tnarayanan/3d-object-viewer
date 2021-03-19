#ifndef MATH_H
#define MATH_H

/*
 * This module provides functions for basic math operations
 * including trigonometry, absolute value, and square root.
 *
 * Author: Tejas Narayanan <tejasn100@gmail.com>
 * Date: Mar 11 2021
 */

#define PI 3.14159

inline float abs(float x) {
	return (x < 0) ? -x : x;
}

/* input angle is in radians */
float sin(float angle);

/* input angle is in radians */
inline float cos(float angle) {
    return sin(PI/2 - angle);
}

/* input angle is in radians */
inline float tan(float angle) {
	return sin(angle) / cos(angle);
}

/* x must be a non-negative number */
float sqrt(float x);

#endif
