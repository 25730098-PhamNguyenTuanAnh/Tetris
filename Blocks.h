#ifndef BLOCKS_H
#define BLOCKS_H

constexpr int H = 20;
constexpr int W = 15;

extern char board[H][W];

class Blocks
{
protected:
    char shape[4][4];
    int x, y;

public:
    Blocks(int startX, int startY);

    virtual ~Blocks() = default;

    void setPosition(int _x, int _y);

    void spawn(char blocks[][4][4], int b);

    bool canMove(int dx, int dy);

    void move(int dx, int dy);

    void toBoard();

    void delFromBoard();

    bool canRotate(char temp[4][4]);

    virtual void rotate();
};

class TBlock : public Blocks {
public:
    TBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {' ','T',' ',' '},
            {'T','T','T',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
    // dùng rotate() mặc định của lớp cha
};

class OBlock : public Blocks {
public:
    OBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {' ','O','O',' '},
            {' ','O','O',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
    void rotate() override {
        // O block không xoay
    }
};

class IBlock : public Blocks {
public:
    IBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '},
            {' ','I',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
    // dùng rotate() mặc định của lớp cha
};

class SBlock : public Blocks {
public:
    SBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {' ','S','S',' '},
            {'S','S',' ',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
};

class ZBlock : public Blocks {
public:
    ZBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {'Z','Z',' ',' '},
            {' ','Z','Z',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
};

class JBlock : public Blocks {
public:
    JBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {'J',' ',' ',' '},
            {'J','J','J',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
};

class LBlock : public Blocks {
public:
    LBlock(int x, int y) : Blocks(x, y) {
        char init[4][4] = {
            {' ',' ',' ',' '},
            {' ',' ','L',' '},
            {'L','L','L',' '},
            {' ',' ',' ',' '}
        };
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = init[i][j];
    }
};

#endif
