#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;
#define H 20
#define W 15
char board[H][W] = {};

int x, y, b;
int speed = 500;
int score = 0; // điểm khi xoá dòng của game
char current[4][4];
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
void spawnBlock(){
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            current[i][j] = blocks[b][i][j];
}
bool canMove(int dx, int dy){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (current[i][j] != ' ') {
                int xt = x + j + dx;
                int yt = y + i + dy;
                if (xt < 1 || xt >= W-1 || yt >= H-1 ) return false;
                if (board[yt][xt] != ' ') return false;
            }
    return true;
}
void block2Board(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (current[i][j] != ' ')
                board[y+i][x+j] = current[i][j];
}
void boardDelBlock(){
    for (int i = 0; i < 4; i++ )
        for (int j = 0; j < 4; j++ )
            if (current[i][j] != ' ')
                board[y+i][x+j] = ' ';
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if (i == 0 || i == H-1 || j ==0 || j == W-1) board[i][j] = '#';
            else board[i][j] = ' ';
}
void draw(){
    system("cls");

    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++) cout<<board[i][j];
}

/* addScore 
* nếu xoá 1 dòng -> thêm 100 điểm
* nếu xoá 2 dòng -> thêm 300 điểm
* nếu xoá 3 dòng -> thêm 500 điểm
* nếu xoá 4 dòng trở lên -> thêm 800 điểm
*/
void addScore(int removedLines){
    if (removedLines == 1) score += 100;
    else if (removedLines == 2) score += 300;
    else if (removedLines == 3) score += 500;
    else if (removedLines >= 4) score += 800;
}

int removeLine(){
    int removed = 0; // diếm số dòng được xoá 
    int i,j;
    for (i = H-2 ; i > 0 ; i-- ){
        for (j = 0 ; j < W ; j++)
            if (board[i][j] == ' ') break;
        if (j == W){
            removed++;
            for (int ii = i ; ii > 0 ; ii--)
                for (int jj = 0; jj < W; jj++)
                    board[ii][jj] = board[ii-1][jj];
            i++;

            // --- LOGIC TĂNG TỐC ---
            if (speed > 100) {
                speed -= 15; // Trừ đi 15ms mỗi lần ăn điểm để khối rơi nhanh hơn
            }
            // ----------------------

            draw();
            _sleep(200);
        }
    }
    return removed; // trả về số dòng được xoá để tính điểm cho game
}
bool canRotate(char temp[4][4]) //xoay khoi 25730140
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

void rotateBlock()
{
    char temp[4][4];

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            temp[j][3 - i] = current[i][j];

    if(canRotate(temp))
    {
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                current[i][j] = temp[i][j];
    }
}
int main()
{
    srand(time(0));
    x = 5; y = 0; b = rand()%7;
    spawnBlock();
    initBoard();
    while (1){
        boardDelBlock();
        if (kbhit()){
            char c = getch();
            if (c == 'a' && canMove(-1,0)) x--;
            if (c == 'd' && canMove( 1,0)) x++;
            if (c == 'x' && canMove( 0,1)) y++;
            if (c == 'w') rotateBlock();
            if (c == 'q') break;
        }
        if (canMove(0,1)) y++;
        else{
            block2Board();
            int removed = removeLine(); // nhận số dòng được xoá từ hàm removeLine()
            if(removed >= 1){
                addScore(removed); // cộng điểm
            }
            x = 5; y = 0; b = rand()%7;
            spawnBlock();
        }
        block2Board();
        draw();
        _sleep(speed);
    }
    return 0;
}
