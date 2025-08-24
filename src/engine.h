#pragma once

#include <raylib.h>

class Engine {
public:
    Engine();
    ~Engine();
    float dt() const;
    void draw_sprite(int id, Vector2 dst) const;
    void play_sound() const;
    void begin_drawing() const;
    void end_drawing() const;
    bool is_running() const;
private:
    Texture2D m_texture{};
    Sound m_sound{};
};