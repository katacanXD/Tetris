#pragma once
#include <vector>
#include <cstdlib> // для rand()
#include <ctime>   // для time()

using namespace std;

enum class BlockType {
    TYPE_0, // I
    TYPE_1, // O  
    TYPE_2, // T
    TYPE_3, // L
    TYPE_4, // J
    TYPE_5, // S
    TYPE_6  // Z
};

struct Block {
    BlockType type;
    vector<vector<int>> shape; // форма фигуры
    int x, y; // позиция на поле
};

class BlockManager { // исправлено название
private:
    vector<vector<vector<int>>> blocks = {
        // TYPE_0 (I-block)
        {
            {1,1,1,1}
        },
        // TYPE_1 (O-block)
        {
            {1,1},
            {1,1}
        },
        // TYPE_2 (T-block)
        {
            {1,1,1},
            {0,1,0}
        },
        // TYPE_3 (L-block)
        {
            {1,1,1},
            {1,0,0}
        },
        // TYPE_4 (J-block)
        {
            {1,1,1},
            {0,0,1}
        },
        // TYPE_5 (S-block)
        {
            {0,1,1},
            {1,1,0}
        },
        // TYPE_6 (Z-block)
        {
            {1,1,0},
            {0,1,1}
        }
    };

public:
    BlockManager() {
        srand(time(nullptr)); // инициализация генератора случайных чисел
    }

    Block createBlock(BlockType type) {
        int index = static_cast<int>(type);
        Block block;
        block.type = type;
        block.shape = blocks[index]; // копируем форму
        block.x = 4; // начальная позиция X
        block.y = 3; // начальная позиция Y
        return block;
    }

    Block createRandomBlock() {
        BlockType randomType = static_cast<BlockType>(rand() % 7);
        return createBlock(randomType);
    }
};