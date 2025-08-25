#include "tracer.h"
#include <raymath.h>
#include "ball.h"
#include "common.h"

void Tracer::trace(Vector2 position, Vector2 velocity) {
    m_path.clear();

    float dt{ 0.020f };
    for (int i = 0; i < 40; i++) {
        velocity = Vector2Add(velocity, Vector2Scale(GRAVITY, dt));
        velocity = Vector2ClampValue(velocity, -MAX_VELOCITY, MAX_VELOCITY);
        position = Vector2Add(position, Vector2Scale(velocity, dt));
        m_path.push_back(position);
    }
}

void Tracer::draw(Engine& e) const {
    for (Vector2 pos : m_path) {
        e.draw_circle(pos, 2.0f, GRAY);
    }
}
