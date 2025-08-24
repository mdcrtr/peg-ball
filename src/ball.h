#pragma once

#include <raylib.h>
#include <vector>
#include "engine.h"
#include "peg.h"

class Ball {
public:
    Ball() = default;
    Ball(Vector2 position);
    void update(Engine& e, std::vector<Peg>& pegs);
    void draw(Engine& e) const;
private:
    Vector2 m_position{};
    Vector2 m_velocity{};

    Peg* get_colliding_peg(std::vector<Peg>& pegs) const;
};
