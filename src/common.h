#pragma once

#include <raylib.h>

constexpr int WIDTH = 1024;
constexpr int HEIGHT = 1024;
constexpr Vector2 GRAVITY{ 0, 700.0f };
constexpr float MAX_VELOCITY{ 1600.0f };
constexpr float LEFT_WALL_X{ 260 };
constexpr float RIGHT_WALL_X{ WIDTH - 260 };

float rand_float(int min, int max);
float clamp(float x, float min, float max);

class Average {
public:
    void update(double val);
    double average() const;
private:
    double m_count{};
    double m_average{};
};