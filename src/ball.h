#pragma once

#include <raylib.h>
#include <vector>
#include "peg.h"

class Ball {
public:
    Ball() = default;
    Ball(Vector2 position);
    void update(std::vector<Peg>& pegs);
    void draw() const;
private:
    Vector2 m_position{};
    Vector2 m_velocity{};

    Peg* get_colliding_peg(std::vector<Peg>& pegs) const;
};
