#include "Blocks.h"

Blocks::Blocks()
{
    x = 5;
    y = 0;
}

void Blocks::setPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}

void Blocks::spawn(char blocks[][4][4], int b)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            shape[i][j] = blocks[b][i][j];
}

bool Blocks::canMove(int dx, int dy)
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(shape[i][j] != ' ')
            {
                int xt = x + j + dx;
                int yt = y + i + dy;

                if(xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;

                if(board[yt][xt] != ' ')
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
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(shape[i][j] != ' ')
                board[y + i][x + j] = shape[i][j];
}

void Blocks::delFromBoard()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(shape[i][j] != ' ')
                board[y + i][x + j] = ' ';
}

bool Blocks::canRotate(char temp[4][4])
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(temp[i][j] != ' ')
            {
                int xt = x + j;
                int yt = y + i;

                if(xt < 1 || xt >= W - 1 || yt >= H - 1)
                    return false;

                if(board[yt][xt] != ' ')
                    return false;
            }

    return true;
}

void Blocks::rotate()
{
    char temp[4][4];

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp[j][3 - i] = shape[i][j];

    if(canRotate(temp))
    {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                shape[i][j] = temp[i][j];
    }
}
