#include "Blocks.h"

Blocks::Blocks(int startX, int startY)
{
    x = startX;
    y = startY;
}

void Blocks::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Blocks::spawn(char blocks[][4][4], int b)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            shape[i][j] = blocks[b][i][j];
}

bool Blocks::canMove(int dx, int dy) const
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shape[i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;

                if (xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;

                if (board[yt][xt] != ' ')
                    return false;
            }

    return true;
}

void Blocks::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

void Blocks::toBoard()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shape[i][j] != ' ')
                board[y + i][x + j] = shape[i][j];
}

void Blocks::delFromBoard()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (shape[i][j] != ' ')
                board[y + i][x + j] = ' ';
}

bool Blocks::canRotate(char temp[4][4]) const
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (temp[i][j] != ' ')
            {
                int xt = x + j;
                int yt = y + i;

                if (xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;

                if (board[yt][xt] != ' ')
                    return false;
            }

    return true;
}

void Blocks::rotate()
{
    char temp[4][4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[j][3 - i] = shape[i][j];

    if (canRotate(temp))
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = temp[i][j];
    }
}

Blocks* createBlock(int type, int startX, int startY) {
    switch (type) {
        case 0: return new IBlock(startX, startY);
        case 1: return new OBlock(startX, startY);
        case 2: return new TBlock(startX, startY);
        case 3: return new SBlock(startX, startY);
        case 4: return new ZBlock(startX, startY);
        case 5: return new LBlock(startX, startY);
        case 6: return new JBlock(startX, startY);
        default: return new TBlock(startX, startY);
    }
}