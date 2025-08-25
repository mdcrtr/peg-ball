#include "board.h"
#include <algorithm>
#include <raymath.h>
#include "common.h"

constexpr float SHOOT_SPEED{ 800.0f };

Board::Board(Engine* engine) : m_engine{ engine }, m_spawn{ WIDTH / 2, 24 } {
    init();
}

void Board::update() {
    switch (m_state) {
    case BoardState::aiming:
        update_aiming();
        break;
    case BoardState::falling:
        update_falling();
        break;
    case BoardState::popping:
        update_popping();
        break;
    case BoardState::lost:
        break;
    case BoardState::won:
        break;
    }

}

void Board::draw() {

    for (const Peg& peg : m_pegs)
        peg.draw(*m_engine);

    m_ball.draw(*m_engine);

    if (m_state == BoardState::aiming) {
        m_tracer.draw(*m_engine);
    }

    m_engine->draw_line({ LEFT_WALL_X, 0 }, { LEFT_WALL_X, HEIGHT });
    m_engine->draw_line({ RIGHT_WALL_X, 0 }, { RIGHT_WALL_X, HEIGHT });
}

bool Board::is_game_over()
{
    return m_state == BoardState::lost || m_state == BoardState::won;
}

void Board::init() {
    for (int y = 300; y < HEIGHT - 100; y += 120) {
        for (int x = LEFT_WALL_X + 60; x < RIGHT_WALL_X - 60; x += 120) {
            float px = x + rand_float(-40, 40);
            float py = y + rand_float(-40, 40);
            m_pegs.push_back({ { px, py } });
        }
    }
}

void Board::update_aiming() {
    Vector2 mouse_pos = GetMousePosition();
    Vector2 direction = Vector2Normalize(Vector2Subtract(mouse_pos, m_spawn));
    Vector2 shoot_vel = Vector2Scale(direction, SHOOT_SPEED);

    m_ball.set_position(m_spawn);
    m_target = Vector2Add(m_spawn, Vector2Scale(direction, 80.0f));
    m_tracer.trace(m_spawn, shoot_vel);

    if (m_engine->is_action_pressed()) {
        m_ball.set_velocity(Vector2Scale(direction, SHOOT_SPEED));
        m_ball.set_last_hit_time(m_engine->time());
        m_state = BoardState::falling;
    }
}

void Board::update_falling() {
    for (Peg& peg : m_pegs)
        peg.update(*m_engine);

    m_ball.update(*m_engine, m_pegs);

    // Detect if the ball has got stuck.
    if (m_engine->time() - m_ball.get_last_hit_time() > 4.0f) {
        m_ball.set_last_hit_time(m_engine->time());
        erase_hit_pegs();
    }

    if (m_ball.get_position().y > HEIGHT) {
        m_state = BoardState::popping;
    }
}

void Board::update_popping() {
    erase_hit_pegs();
    if (m_pegs.size() == 0) {
        m_state = BoardState::won;
    }
    else {
        m_state = BoardState::aiming;
    }
}

void Board::erase_hit_pegs() {
    std::erase_if(m_pegs, [](const Peg& p) {
        return p.was_hit();
        });
}
