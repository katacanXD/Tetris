#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include "Block.h"

class Board {
private:
    static const int height = 22;
    static const int width = 12;
    std::vector<std::vector<int>> grid;

    int score = 0;

public:
    int getScore() const { return score; }  // геттер для доступа к score

    Board() {
        grid.resize(height, std::vector<int>(width, 0));
        // границы
        for (int i = 0; i < height; ++i) {
            grid[i][0] = 9;
            grid[i][width - 1] = 9;
        }
        for (int j = 0; j < width; ++j) {
            grid[height - 1][j] = 9;
        }
    }

    bool checkCollision(const Block& block) {
        for (int i = 0; i < block.shape.size(); ++i) {
            for (int j = 0; j < block.shape[i].size(); ++j) {
                if (block.shape[i][j]) {
                    int x = block.x + j;
                    int y = block.y + i;
                    if (y >= height || x < 0 || x >= width || grid[y][x])
                        return true;
                }
            }
        }
        return false;
    }

    void addBlock(const Block& block) {
        for (int i = 0; i < block.shape.size(); ++i) {
            for (int j = 0; j < block.shape[i].size(); ++j) {
                if (block.shape[i][j]) {
                    grid[block.y + i][block.x + j] = 1;
                }
            }
        }
    }

    void render(const Block* current) {
        // переместить курсор в левый верхний угол (0, 0)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(hConsole, coord);

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                bool filled = grid[i][j] != 0;

                if (current) {
                    int bx = j - current->x;
                    int by = i - current->y;
                    if (by >= 0 && by < current->shape.size() &&
                        bx >= 0 && bx < current->shape[by].size() &&
                        current->shape[by][bx])
                        filled = true;
                }

                if (grid[i][j] == 9)
                    std::cout << "##";
                else
                    std::cout << (filled ? "[]" : "  ");
            }
            std::cout << std::endl;
        }
    }


    void clearFullLines() {
        int linesCleared = 0;  // Счетчик очищенных линий

        for (int i = height - 2; i >= 0; --i) {
            bool full = true;

            // Проверяем, заполнена ли текущая линия
            for (int j = 1; j < width - 1; ++j) {
                if (!grid[i][j]) {
                    full = false;
                    break;
                }
            }

            // Если линия заполнена - очищаем ее
            if (full) {
                for (int k = i; k > 0; --k)
                    grid[k] = grid[k - 1];
                grid[0] = std::vector<int>(width, 0);
                grid[0][0] = 9;
                grid[0][width - 1] = 9;
                ++i;  // Проверяем ту же позицию снова (так как все сдвинулось вниз)
                linesCleared++;
            }
        }

        if (linesCleared > 0) {
            score += linesCleared * 100;

            // if (linesCleared == 1) score += 100;
            // else if (linesCleared == 2) score += 300;
            // else if (linesCleared == 3) score += 500;
            // else if (linesCleared == 4) score += 800;
        }
    }
};
