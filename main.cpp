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

const char* CELL_BORDER = "##";
const char* CELL_EMPTY = "  ";
const char* CELL_BLOCK = "[]";

int blockType;
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

// Ve board ra terminal. Moi o duoc in bang hai ky tu de luoi nhin vuong vuc hon.
void draw()
{
    system("cls");

    for (int i = 0 ; i < H ; i++, cout << endl)
        for (int j = 0 ; j < W ; j++) {
            if (board[i][j] == '#')      cout << CELL_BORDER;
            else if (board[i][j] == ' ') cout << CELL_EMPTY;
            else                         cout << CELL_BLOCK;
        }
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
     // Doi tuong quan ly khoi dang roi
    Blocks currentBlock;

    blockType = rand() % 7;
    currentBlock.spawn(blocks, blockType);

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
            blockType = rand() % 7;
            currentBlock.spawn(blocks, blockType);
        }

        currentBlock.toBoard();
        draw();
        _sleep(speed);
    }

    return 0;
}
