#include "peg.h"
#include <raymath.h>

Peg::Peg(Vector2 position) : m_position{ position } {}

void Peg::update(Engine& e) {
    if (m_hit_cooldown > 0) {
        m_hit_cooldown -= e.dt();
    }
}

void Peg::draw(Engine& e) const {
    int id = m_hit_cooldown > 0 ? 2 : 1;
    e.draw_sprite(id, Vector2SubtractValue(m_position, 16.0f));
}

void Peg::hit(Engine& e) {
    if (m_hit_cooldown <= 0.0f)
        e.play_sound();
    m_hit_cooldown = 0.25f;
}

Vector2 Peg::position() const {
    return m_position;
}