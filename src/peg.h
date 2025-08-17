#pragma once

#include <raylib.h>

class Peg {
public:
    Peg() = default;
    Peg(Vector2 position);
    void update();
    void draw() const;
    void hit();
    Vector2 position() const;
private:
    Vector2 m_position{};
    Color m_color{ WHITE };
    float m_hit_cooldown{};
};