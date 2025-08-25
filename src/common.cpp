#include "common.h"

float rand_float(int min, int max) {
    return static_cast<float>(GetRandomValue(min, max));
}

float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void Average::update(double val) {
    m_count++;
    m_average += (val - m_average) / m_count;
}

double Average::average() const {
    return m_average;
}