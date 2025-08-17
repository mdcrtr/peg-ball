#include <raylib.h>
#include <vector>
#include "ball.h"
#include "common.h"
#include "peg.h"

using std::vector;

float rand_float(int min, int max) {
    return static_cast<float>(GetRandomValue(min, max));
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Peg Ball");
    SetTargetFPS(60);

    Ball ball{ {WIDTH / 2, 0} };
    vector<Peg> pegs;

    Average av;

    for (int i = 0; i < 200; i++) {
        pegs.push_back({ {rand_float(0, WIDTH), rand_float(40, HEIGHT) } });
    }

    while (!WindowShouldClose()) {
        double t1 = GetTime();
        if (IsKeyPressed(KEY_SPACE)) {
            float bx = WIDTH / 2.0f + rand_float(-20, 20);
            ball = Ball{ {bx, 0} };
        }

        for (Peg& peg : pegs)
            peg.update();

        ball.update(pegs);
        BeginDrawing();
        ClearBackground(BLACK);
        ball.draw();

        for (const Peg& peg : pegs)
            peg.draw();

        double t2 = GetTime();
        av.update(t2 - t1);
        const char* txt = TextFormat("%.6f", av.average());
        DrawText(txt, 0, 0, 32, GREEN);
        EndDrawing();
    }

    CloseWindow();
}