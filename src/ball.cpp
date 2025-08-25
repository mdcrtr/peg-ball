#include "ball.h"
#include "common.h"
#include <raymath.h>
#include <cmath>

using std::vector;

Ball::Ball(Vector2 position) : m_position{ position } {}

void Ball::update(Engine& e, vector<Peg>& pegs) {
    float dt = e.dt();
    Vector2 old_position = m_position;

    m_velocity = Vector2Add(m_velocity, Vector2Scale(GRAVITY, dt));
    m_velocity = Vector2ClampValue(m_velocity, -MAX_VELOCITY, MAX_VELOCITY);
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, dt));

    Peg* peg = get_colliding_peg(pegs);
    if (peg != nullptr) {
        Vector2 normal = Vector2Normalize(Vector2Subtract(m_position, peg->position()));
        m_velocity = Vector2Reflect(m_velocity, normal);
        m_velocity = Vector2Scale(m_velocity, 0.8);
        m_position = old_position;

        if (!peg->was_hit()) {
            m_last_hit_time = e.time();
        }

        peg->hit(e);
    }

    if (m_position.x < LEFT_WALL_X + 16.0f || m_position.x > RIGHT_WALL_X - 16.0f)
        m_velocity.x *= -1.0f;
}

void Ball::draw(Engine& e) const {
    e.draw_sprite(0, Vector2SubtractValue(m_position, 16.0f));
}

void Ball::set_position(Vector2 position) {
    m_position = position;
}

void Ball::set_velocity(Vector2 velocity) {
    m_velocity = velocity;
}

Vector2 Ball::get_position() const {
    return m_position;
}

double Ball::get_last_hit_time() const {
    return m_last_hit_time;
}

void Ball::set_last_hit_time(double time) {
    m_last_hit_time = time;
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