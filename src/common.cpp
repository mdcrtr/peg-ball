#include "common.h"

void Average::update(double val) {
    m_count++;
    m_average += (val - m_average) / m_count;
}

double Average::average() const {
    return m_average;
}