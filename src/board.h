#pragma once

#include <vector>
#include <raylib.h>
#include "engine.h"
#include "ball.h"
#include "peg.h"
#include "tracer.h"

enum class BoardState { aiming, falling, popping, won, lost };

class Board {
public:
    Board(Engine* engine);
    void update();
    void draw();
    bool is_game_over();
private:
    Engine* m_engine;
    Ball m_ball;
    Tracer m_tracer;
    Vector2 m_spawn;
    Vector2 m_target;
    std::vector<Peg> m_pegs;
    BoardState m_state{ BoardState::aiming };

    void init();
    void update_aiming();
    void update_falling();
    void update_popping();
    void erase_hit_pegs();
};
