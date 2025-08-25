#include "engine.h"
#include "common.h"

constexpr Rectangle atlas[]{
    {0, 0, 32, 32},
    {32, 0, 32, 32},
    {64, 0, 32, 32},
};

Engine::Engine() : m_inited{ true } {
    InitWindow(WIDTH, HEIGHT, "Peg Ball");
    SetTargetFPS(60);
    InitAudioDevice();
    m_texture = LoadTexture("assets/balls.png");
    m_sound = LoadSound("assets/peg.wav");
}

Engine::Engine(Engine&& o) : m_texture{ o.m_texture }, m_sound{ o.m_sound }, m_inited{ true }
{
    o.m_inited = false;
}

Engine& Engine::operator=(Engine&& o)
{
    m_texture = o.m_texture;
    m_sound = o.m_sound;
    m_inited = true;
    o.m_inited = false;
    return *this;
}

Engine::~Engine() {
    if (!m_inited) return;

    UnloadSound(m_sound);
    UnloadTexture(m_texture);
    CloseAudioDevice();
    CloseWindow();
}

float Engine::dt() const {
    return GetFrameTime();
}

double Engine::time() const
{
    return GetTime();
}

void Engine::draw_line(Vector2 point1, Vector2 point2, Color color) const
{
    DrawLineV(point1, point2, color);
}

void Engine::draw_sprite(int id, Vector2 dst, Color color) const {
    Rectangle src = atlas[id];
    DrawTextureRec(m_texture, src, dst, color);
}

void Engine::draw_text(std::string text, Vector2 point, Color color) const
{
    DrawText(text.c_str(), static_cast<int>(point.x), static_cast<int>(point.y), 32, color);
}

void Engine::play_sound() const {
    PlaySound(m_sound);
}

void Engine::begin_drawing() const {
    BeginDrawing();
    ClearBackground(BLACK);
}

void Engine::end_drawing() const {
    EndDrawing();
}

bool Engine::is_running() const {
    return !WindowShouldClose();
}

bool Engine::is_action_pressed() const
{
    return IsKeyPressed(KEY_SPACE);
}
