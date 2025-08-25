#include "common.h"
#include "engine.h"
#include "board.h"

struct AppState {
    Engine engine;
    Board board;

    AppState() : engine{}, board{ &engine } {}
};

void iterate(AppState* app) {
    if (app->board.is_game_over()) {
        app->board = Board{ &app->engine };
    }

    app->board.update();

    app->engine.begin_drawing();
    app->board.draw();
    app->engine.end_drawing();
}

int main() {
    AppState app;

    while (app.engine.is_running()) {
        iterate(&app);
    }

    return 0;
}