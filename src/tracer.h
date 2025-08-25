#pragma once

#include <vector>
#include "engine.h"

class Tracer {
public:
    void trace(Vector2 position, Vector2 velocity);
    void draw(Engine& e) const;
private:
    std::vector<Vector2> m_path;
};