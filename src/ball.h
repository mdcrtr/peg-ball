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
    void set_position(Vector2 position);
    void set_velocity(Vector2 velocity);
    Vector2 get_position() const;
    void set_last_hit_time(double time);
    double get_last_hit_time() const;
private:
    Vector2 m_position{};
    Vector2 m_velocity{};
    double m_last_hit_time{};

    Peg* get_colliding_peg(std::vector<Peg>& pegs) const;
};
