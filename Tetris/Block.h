#pragma once
#include <vector>
#include <cstdlib>
#include <ctime>

enum class BlockType {
    I, O, T, L, J, S, Z
};

struct Block {
    BlockType type;
    std::vector<std::vector<int>> shape;
    int x;
    int y;
};

class BlockManager {
private:
    const std::vector<std::vector<std::vector<int>>> shapes = {
        {{1,1,1,1}},                 // I
        {{1,1},{1,1}},               // O
        {{1,1,1},{0,1,0}},           // T
        {{1,1,1},{1,0,0}},           // L
        {{1,1,1},{0,0,1}},           // J
        {{0,1,1},{1,1,0}},           // S
        {{1,1,0},{0,1,1}}            // Z
    };

public:
    BlockManager() {
        srand((unsigned)time(nullptr));
    }

    Block createBlock(BlockType type) {
        int i = static_cast<int>(type);
        Block b;
        b.type = type;
        b.shape = shapes[i];
        b.x = 4;
        b.y = 0;
        return b;
    }

    Block createRandomBlock() {
        return createBlock(static_cast<BlockType>(rand() % 7));
    }
};
