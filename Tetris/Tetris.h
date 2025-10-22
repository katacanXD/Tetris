#pragma once
#include <functional>
#include <chrono>
#include <thread>
#include "Board.h"
#include <windows.h>

class Tetris {
private:
    Board board;
    BlockManager blockManager;
    Block currentBlock;
    bool hasBlock = false;
    bool running = false;
    float tickInterval = 1.0f;

public:
    void start() {
        running = true;
        auto lastTick = std::chrono::steady_clock::now();

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

            // управление
            if (GetAsyncKeyState(0x41)) moveLeft();
            if (GetAsyncKeyState(0x44)) moveRight();
            if (GetAsyncKeyState(0x53)) moveDown();

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

        board.render(&currentBlock);

        tickInterval *= 0.98f;
        std::cout << tickInterval << std::endl;
    }

    void rotate() {
        Block temp = currentBlock;
        
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
