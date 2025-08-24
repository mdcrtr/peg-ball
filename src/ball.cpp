#include "ball.h"
#include "common.h"
#include <raymath.h>
#include <cmath>

using std::vector;

Ball::Ball(Vector2 position) : m_position{ position } {}

void Ball::update(Engine& e, vector<Peg>& pegs) {
    float dt = GetFrameTime();
    Vector2 old_position = m_position;

    m_velocity = Vector2Add(m_velocity, Vector2Scale(GRAVITY, dt));
    m_velocity = Vector2ClampValue(m_velocity, -400.0f, 400.0f);
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, dt));

    Peg* peg = get_colliding_peg(pegs);
    if (peg != nullptr) {
        peg->hit(e);
        Vector2 normal = Vector2Normalize(Vector2Subtract(m_position, peg->position()));
        m_velocity = Vector2Reflect(m_velocity, normal);
        m_velocity = Vector2Scale(m_velocity, 0.8);
        m_position = old_position;
    }

    if (m_position.y > HEIGHT)
        m_position.y = 0;

    if (m_position.x < 0 || m_position.x > WIDTH)
        m_velocity.x *= -1.0f;
}

void Ball::draw(Engine& e) const {
    e.draw_sprite(0, Vector2SubtractValue(m_position, 16.0f));
}

Peg* Ball::get_colliding_peg(vector<Peg>& pegs) const {
    float radius_sqr = 24.0f * 24.0f;
    for (Peg& peg : pegs) {
        Vector2 pos = peg.position();
        if (Vector2DistanceSqr(m_position, pos) < radius_sqr) {
            return &peg;
        }
    }
    return nullptr;
}