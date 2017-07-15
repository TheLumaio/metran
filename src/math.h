#ifndef MATH_H
#define MATH_H

#define MATH_PI 3.1415926535

inline double to_radians(int degrees) {
    return degrees * MATH_PI / 180.0;
}

inline int to_degrees(double radians) {
    return radians * 180.0 / MATH_PI;
}

#endif

