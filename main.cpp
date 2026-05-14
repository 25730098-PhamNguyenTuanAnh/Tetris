#include "Blocks.h"
#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

char board[H][W] = {};

const int SCORE_SINGLE = 100;
const int SCORE_DOUBLE = 300;
const int SCORE_TRIPLE = 500;
const int SCORE_TETRIS = 800;

const int SPEED_STEP = 15;

int speed = 500;
int score = 0;

void initBoard()
{
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j == 0 || j == W-1)
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}

void draw()
{
    system("cls");

    for (int i = 0 ; i < H ; i++, cout << endl)
        for (int j = 0 ; j < W ; j++)
            cout << board[i][j];
}

void addScore(int removedLines)
{
    if (removedLines == 1) score += SCORE_SINGLE;
    else if (removedLines == 2) score += SCORE_DOUBLE;
    else if (removedLines == 3) score += SCORE_TRIPLE;
    else if (removedLines >= 4) score += SCORE_TETRIS;
}

int removeLine()
{
    int removed = 0;
    int i, j;

    for (i = H - 2 ; i > 0 ; i--)
    {
        for (j = 0 ; j < W ; j++)
            if (board[i][j] == ' ')
                break;

        if (j == W)
        {
            removed++;

            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii - 1][jj];

            i++;

            if (speed > 100)
                speed -= SPEED_STEP;

            draw();
            _sleep(200);
        }
    }

    return removed;
}

int main()
{
    srand(time(0));
    initBoard();
    Blocks* current = createBlock(rand() % 7, 5, 0);

    while (1){
        current->delFromBoard();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && current->canMove(-1, 0)) current->moveX(-1);
            if (c == 'd' && current->canMove( 1, 0)) current->moveX( 1);
            if (c == 'x' && current->canMove( 0, 1)) current->moveY( 1);
            if (c == 'w') current->rotate();
            if (c == 'q') break;
        }
        if (current->canMove(0, 1)) current->moveY(1);
        else
        {
            current->toBoard();
            int removed = removeLine();
            if (removed >= 1) addScore(removed);
            delete current;
            current = createBlock(rand() % 7, 5, 0);
        }

        current->toBoard();
        draw();
        _sleep(speed);
    }
    delete current;
    return 0;
}
