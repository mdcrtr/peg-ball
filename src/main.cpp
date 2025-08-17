#include <raylib.h>
#include <raymath.h>
#include <optional>
#include <vector>

using std::optional, std::vector;

constexpr Vector2 GRAVITY{ 0, 60 };

class Peg {
public:
    Peg() = default;
    Peg(Vector2 position);
    void draw() const;
    Vector2 position() const;
private:
    Vector2 m_position{};
};

Peg::Peg(Vector2 position) : m_position{ position } {}

void Peg::draw() const {
    DrawCircleV(m_position, 8, WHITE);
}

Vector2 Peg::position() const {
    return m_position;
}

class Ball {
public:
    Ball() = default;
    Ball(Vector2 position);
    void update(const vector<Peg>& pegs);
    void draw() const;
private:
    Vector2 m_position{};
    Vector2 m_velocity{};

    optional<const Peg> get_colliding_peg(const vector<Peg>& pegs) const;
};

Ball::Ball(Vector2 position) : m_position{ position } {}

void Ball::update(const vector<Peg>& pegs) {
    float dt = GetFrameTime();
    Vector2 old_position = m_position;

    m_velocity = Vector2Add(m_velocity, Vector2Scale(GRAVITY, dt));
    m_position = Vector2Add(m_position, Vector2Scale(m_velocity, dt));

    optional<const Peg> peg = get_colliding_peg(pegs);
    if (peg.has_value()) {
        Vector2 normal = Vector2Normalize(Vector2Subtract(m_position, peg->position()));
        m_velocity = Vector2Reflect(m_velocity, normal);
        m_velocity = Vector2Scale(m_velocity, 0.8);
        m_position = old_position;
    }
}

void Ball::draw() const {
    DrawCircleV(m_position, 8, RED);
}

optional<const Peg> Ball::get_colliding_peg(const vector<Peg>& pegs) const {
    float radius_sqr = 16 * 16;
    for (const Peg& peg : pegs) {
        if (Vector2DistanceSqr(m_position, peg.position()) < radius_sqr) {
            return peg;
        }
    }
    return std::nullopt;
}

float rand_float(int min, int max) {
    return static_cast<float>(GetRandomValue(min, max));
}

int main() {
    InitWindow(1280, 720, "Peg Ball");
    SetTargetFPS(60);

    Ball ball{ {640, 0} };
    vector<Peg> pegs;

    for (int i = 0; i < 200; i++) {
        pegs.push_back({ {rand_float(0, 1280), rand_float(40, 720) } });
    }

    while (!WindowShouldClose()) {
        ball.update(pegs);
        BeginDrawing();
        ClearBackground(BLACK);
        ball.draw();
        for (const Peg& peg : pegs)
            peg.draw();
        EndDrawing();
    }

    CloseWindow();
}