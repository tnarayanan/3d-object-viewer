#ifndef MATH_H
#define MATH_H

#define PI 3.14159

/* absolute value */
#define abs(x) (((x) < 0) ? (-(x)) : (x))

/* angle in radians */
double sin(double angle);

/* angle in radians */
inline double cos(double angle) {
    return sin(angle - PI/2);
}

/* angle in radians */
inline double tan(double angle) {
	return sin(angle) / cos(angle);
}

double sqrt(double x);

#endif
