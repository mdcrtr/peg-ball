#pragma once

#include <string>
#include <raylib.h>

class Engine {
public:
    Engine();
    Engine(const Engine& o) = delete;
    Engine(Engine&& o);
    Engine& operator=(const Engine& o) = delete;
    Engine& operator=(Engine&& o);

    ~Engine();

    float dt() const;
    double time() const;
    void draw_line(Vector2 point1, Vector2 point2, Color color = WHITE) const;
    void draw_sprite(int id, Vector2 dst, Color color = WHITE) const;
    void draw_text(std::string text, Vector2 point, Color color = WHITE) const;
    void play_sound() const;
    void begin_drawing() const;
    void end_drawing() const;
    bool is_running() const;
    bool is_action_pressed() const;
private:
    Texture2D m_texture{};
    Sound m_sound{};
    bool m_inited{};
};