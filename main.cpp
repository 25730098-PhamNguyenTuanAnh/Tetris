#include "Blocks.h"
#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

char board[H][W] = {};

int b;
int speed = 500;
int score = 0;
char blocks[][4][4] ={
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

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
    if (removedLines == 1) score += 100;
    else if (removedLines == 2) score += 300;
    else if (removedLines == 3) score += 500;
    else if (removedLines >= 4) score += 800;
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
                speed -= 15;

            draw();
            _sleep(200);
        }
    }

    return removed;
}

int main()
{
    srand(time(0));

    Blocks currentBlock;

    b = rand() % 7;
    currentBlock.spawn(blocks, b);

    initBoard();

    while (1)
    {
        currentBlock.delFromBoard();

        if (kbhit())
        {
            char c = getch();

            if (c == 'a' && currentBlock.canMove(-1, 0))
                currentBlock.move(-1, 0);

            if (c == 'd' && currentBlock.canMove(1, 0))
                currentBlock.move(1, 0);

            if (c == 'x' && currentBlock.canMove(0, 1))
                currentBlock.move(0, 1);

            if (c == 'w')
                currentBlock.rotate();

            if (c == 'q')
                break;
        }

        if (currentBlock.canMove(0, 1))
        {
            currentBlock.move(0, 1);
        }
        else
        {
            currentBlock.toBoard();

            int removed = removeLine();

            if (removed >= 1)
            {
                addScore(removed);
            }

            currentBlock.setPosition(5, 0);
            b = rand() % 7;
            currentBlock.spawn(blocks, b);
        }

        currentBlock.toBoard();
        draw();
        _sleep(speed);
    }

    return 0;
}
