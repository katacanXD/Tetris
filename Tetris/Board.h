#pragma once
#include <iostream>

#include "Block.h"

using namespace std;

class Board
{
private:
    static const short int height = 22, length = 12;
    bool board[height][length];

public:
    Board() {
        fill();
    }

    void render() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < length; ++j) {
                if (board[i][j]) {
                    if ((i == 0 || i == height - 1) && (j == 0 || j == length - 1)) {
                        cout << "+"; // углы
                    }
                    else if (i == 0 || i == height - 1) {
                        cout << "--"; // горизонтальные линии
                    }
                    else if (j == 0 || j == length - 1) {
                        cout << "|"; // вертикальные линии
                    }
                    else {
                        cout << "##"; // внутренние ячейки
                    }
                }
                else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }

    BlockManager blockManager;
    static Block currentBlock;


private:
    void fill() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < length; ++j) {
                board[i][j] = (i == 0 || j == 0 || i == height - 1 || j == length - 1);
            }
        }

        currentBlock = blockManager.createRandomBlock();

        if (currentBlock.type != BlockType::TYPE_0 && currentBlock.type != BlockType::TYPE_1) {
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[currentBlock.y + i][currentBlock.x + j] == 0) {
                        board[currentBlock.y + i][currentBlock.x + j] = currentBlock.shape[i][j];
                    }
                }
            }
        }
    }
};