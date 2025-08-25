#include <raylib.h>
#include <format>
#include <string>
#include <vector>
#include "ball.h"
#include "common.h"
#include "engine.h"
#include "peg.h"


float rand_float(int min, int max) {
    return static_cast<float>(GetRandomValue(min, max));
}

float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

int main() {
    Engine engine;
    Average av;

    std::vector<Ball> balls{ Vector2{WIDTH / 2, 0}, Vector2{WIDTH / 2 - 100, 0}, Vector2{WIDTH / 2 + 100, 0} };
    std::vector<Peg> pegs;

    for (int y = 220; y < HEIGHT - 40; y += 100) {
        for (int x = LEFT_WALL_X; x < RIGHT_WALL_X; x += 100) {
            float px = clamp(x + rand_float(-40, 40), LEFT_WALL_X + 24.0f, RIGHT_WALL_X - 24.0f);
            float py = y + rand_float(-40, 40);
            pegs.push_back({ { px, py } });
        }
    }

    while (engine.is_running()) {
        double t1 = engine.time();
        if (engine.is_action_pressed()) {
            for (Ball& ball : balls) {
                float bx = WIDTH / 2.0f + rand_float(-100, 100);
                ball = Ball{ {bx, 0} };
            }
        }

        for (Peg& peg : pegs)
            peg.update(engine);

        for (Ball& ball : balls)
            ball.update(engine, pegs);

        engine.begin_drawing();

        for (const Peg& peg : pegs)
            peg.draw(engine);

        for (Ball& ball : balls)
            ball.draw(engine);

        engine.draw_line({ LEFT_WALL_X, 0 }, { LEFT_WALL_X, HEIGHT });
        engine.draw_line({ RIGHT_WALL_X, 0 }, { RIGHT_WALL_X, HEIGHT });

        double t2 = engine.time();
        av.update(t2 - t1);
        std::string text = std::format("{:.6f}", av.average());
        engine.draw_text(text, { 10, 10 }, GREEN);
        engine.end_drawing();
    }
}