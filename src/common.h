#pragma once

#include <raylib.h>

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 1024;
constexpr Vector2 GRAVITY{ 0, 200 };

class Average {
public:
    void update(double val);
    double average() const;
private:
    double m_count{};
    double m_average{};
};