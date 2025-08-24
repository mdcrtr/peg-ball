#pragma once

#include <raylib.h>
#include "engine.h"

class Peg {
public:
    Peg() = default;
    Peg(Vector2 position);
    void update(Engine& e);
    void draw(Engine& e) const;
    void hit(Engine& e);
    Vector2 position() const;
private:
    Vector2 m_position{};
    Color m_color{ WHITE };
    float m_hit_cooldown{};
};