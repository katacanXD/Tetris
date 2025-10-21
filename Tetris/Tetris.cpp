#include "Board.h"
#include "Block.h"

using namespace std;

#include <chrono>
#include <thread>
#include <functional>
#include <iostream>

class Tetris {
private:
    using TickCallback = std::function<void()>;

    TickCallback gameTickCallback;
    float tickInterval = 1.0f; // секунды
    bool running = false;

public:
    void setTickCallback(TickCallback callback) {
        gameTickCallback = callback;
    }

    void start() {
        running = true;
        auto lastTick = std::chrono::steady_clock::now();

        while (running) {
            auto now = std::chrono::steady_clock::now();
            float elapsed = std::chrono::duration<float>(now - lastTick).count();

            if (elapsed >= tickInterval) {
                if (gameTickCallback) {
                    gameTickCallback();
                }
                lastTick = now;

                // Ускоряем игру
                //tickInterval *= 0.99f;
                //if (tickInterval < 0.1f) tickInterval = 0.1f;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void stop() { running = false; }
};

Board gameBoard;
// Использование:
int main() {
    gameBoard.render();

    Tetris game;

    game.setTickCallback([]() {
        system("cls");
        //// Игровая логика
        gameBoard.render();
        });

    game.start();
    return 0;
}