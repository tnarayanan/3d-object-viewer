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

inline double abs(double x) {
	return (x < 0) ? -x : x;
}

/* input angle is in radians */
double sin(double angle);

/* input angle is in radians */
inline double cos(double angle) {
    return sin(angle - PI/2);
}

/* input angle is in radians */
inline double tan(double angle) {
	return sin(angle) / cos(angle);
}

/* x must be a non-negative number */
double sqrt(double x);

#endif
