#include "peg.h"

Peg::Peg(Vector2 position) : m_position{ position } {}

void Peg::update() {
    if (m_hit_cooldown > 0) {
        m_hit_cooldown -= GetFrameTime();
    }
}

void Peg::draw() const {
    float radius = m_hit_cooldown > 0.0f ? 10 : 6;
    DrawCircleSector(m_position, radius, 0, 360, 8, m_color);
}

void Peg::hit() {
    m_hit_cooldown = 0.25f;
    m_color = GREEN;
}

Vector2 Peg::position() const {
    return m_position;
}