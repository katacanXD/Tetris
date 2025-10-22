#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include "Board.h"
#include <windows.h>
#include <vector>

class Tetris {
private:
    Board board;
    BlockManager blockManager;
    Block currentBlock;
    bool hasBlock = false;
    bool running = false;
    float tickInterval = 1.0f;

    // Для кд управления
    std::chrono::steady_clock::time_point lastInputTime;
    float inputCooldown = 0.1f; // 200ms cooldown

public:
    void start() {
        running = true;
        auto lastTick = std::chrono::steady_clock::now();
        lastInputTime = std::chrono::steady_clock::now(); // Инициализируем время последнего ввода

        while (running) {
            auto now = std::chrono::steady_clock::now();
            float elapsed = std::chrono::duration<float>(now - lastTick).count();

            if (!hasBlock) {
                currentBlock = blockManager.createRandomBlock();
                hasBlock = true;
                if (board.checkCollision(currentBlock)) {
                    std::cout << "Game Over!\n";
                    running = false;
                    break;
                }
            }

            if (elapsed >= tickInterval) {
                tick();
                lastTick = now;
            }

            // Проверяем кд для ввода
            float inputElapsed = std::chrono::duration<float>(now - lastInputTime).count();
            if (inputElapsed >= inputCooldown) {
                if (GetAsyncKeyState(0x41)) { // A
                    moveLeft();
                    lastInputTime = now;
                }
                else if (GetAsyncKeyState(0x44)) { // D
                    moveRight();
                    lastInputTime = now;
                }
                else if (GetAsyncKeyState(0x53)) { // S
                    moveDown();
                    lastInputTime = now;
                }
                else if (GetAsyncKeyState(VK_UP)) { // UP
                    rotate();
                    lastInputTime = now;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }

private:
    void tick() {
        Block temp = currentBlock;
        temp.y += 1;
        if (!board.checkCollision(temp)) {
            currentBlock = temp;
        }
        else {
            board.addBlock(currentBlock);
            board.clearFullLines();
            hasBlock = false;
        }

        // Ускоряем игру в зависимости от счета
        if (board.getScore() >= 1000 && board.getScore() < 10000) {
            tickInterval = 0.8f;
        }
        else if (board.getScore() >= 10000 && board.getScore() < 100000) {
            tickInterval = 0.5f;
        }
        else if (board.getScore() >= 100000) {
            tickInterval = 0.2f;
        }

        board.render(&currentBlock);
        std::cout << "Your score: " << board.getScore() << std::endl;
    }

    void rotate() {
        Block temp = currentBlock;

        int rows = temp.shape.size();
        int cols = temp.shape[0].size();
        std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows, 0));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                rotated[j][rows - 1 - i] = temp.shape[i][j];
            }
        }

        temp.shape = rotated;

        if (!board.checkCollision(temp)) {
            currentBlock = temp;
            board.render(&currentBlock);
        }
    }

    void moveLeft() {
        Block temp = currentBlock;
        temp.x -= 1;
        if (!board.checkCollision(temp)) {
            currentBlock = temp;
            board.render(&currentBlock);
        }
    }

    void moveRight() {
        Block temp = currentBlock;
        temp.x += 1;
        if (!board.checkCollision(temp)) {
            currentBlock = temp;
            board.render(&currentBlock);
        }
    }

    void moveDown() {
        Block temp = currentBlock;
        temp.y += 1;
        if (!board.checkCollision(temp)) {
            currentBlock = temp;
            board.render(&currentBlock);
        }
        else {
            board.addBlock(currentBlock);
            board.clearFullLines();
            hasBlock = false;
        }
    }
};