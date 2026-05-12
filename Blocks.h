#ifndef BLOCKS_H
#define BLOCKS_H

#define H 20
#define W 15

extern char board[H][W];
// Class quan ly khoi Tetris dang roif
class Blocks
{
private:
    char shape[4][4];
    int x, y;

public:
    Blocks();

    void setPosition(int _x, int _y);

    void spawn(char blocks[][4][4], int b);// Copy hinh dang khoi vao shape

    // Kiem tra khoi co the di chuyen hay khongg
    bool canMove(int dx, int dy);
    // Di chuyen khoi theo dx, dy
    void move(int dx, int dy);
    // Ghi khoi hien tai len board
    void toBoard();

    void delFromBoard();

    bool canRotate(char temp[4][4]);

    virtual void rotate();
};

#endif
