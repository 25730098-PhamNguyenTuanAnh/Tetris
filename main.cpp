#include "Blocks.h"
#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;

char board[H][W] = {};

const int LEVEL_SCORE_STEP = 1000;
const int MAX_LEVEL = 10;
const int MIN_SPEED = 100;

int level = 1;

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
int totalLinesCleared = 0;
int totalPiecesPlaced = 0;
time_t gameStartTime;

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

    cout << "Score: " << score << " | Level: " << level << " | Speed: " << speed << endl;

    for (int i = 0 ; i < H ; i++, cout << endl)
        for (int j = 0 ; j < W ; j++)
        {
            switch (board[i][j])
            {
                case '#': cout << CELL_BORDER; break;
                case ' ': cout << CELL_EMPTY;  break;
                default:  cout << CELL_BLOCK;  break;
            }
        }
}

void addScore(int removedLines)
{
    if (removedLines == 1) score += SCORE_SINGLE;
    else if (removedLines == 2) score += SCORE_DOUBLE;
    else if (removedLines == 3) score += SCORE_TRIPLE;
    else if (removedLines >= 4) score += SCORE_TETRIS;
}

void updateLevel()
{
    // Level tăng mỗi khi score đạt thêm 1000 điểm
    level = score / LEVEL_SCORE_STEP + 1;

    // Giới hạn level tối đa để game không tăng tốc vô hạn
    if (level > MAX_LEVEL)
        level = MAX_LEVEL;

    // Speed càng nhỏ thì block rơi càng nhanh
    speed = 500 - (level - 1) * SPEED_STEP;

    // Giới hạn speed tối thiểu để game vẫn còn chơi được
    if (speed < MIN_SPEED)
        speed = MIN_SPEED;
}

int removeLine()
{
    int removed = 0;
    int i, j;

    // Duyệt từ dưới lên trên
    // Bỏ qua hàng cuối vì đó là tường '#'
    for (i = H - 2 ; i > 0 ; i--)
    {
        for (j = 1 ; j < W - 1 ; j++)

            if (board[i][j] == ' ')
                break;

        if (j == W - 1)
        {
            removed++;

            for (int ii = i ; ii > 0 ; ii--)
                // Chỉ copy phần bên trong board
                // Không copy phần tường '#'
                for (int jj = 1; jj < W - 1; jj++)
                    board[ii][jj] = board[ii - 1][jj];// Line hiện tại nhận dữ liệu từ line phía trên

            // Sau khi kéo line xuống:
            // row[1] sẽ bị duplicate dữ liệu cũ
            // vì không có row phía trên để copy xuống
            // -> cần reset lại hàng đầu tiên
            for (int jj = 1; jj < W - 1; jj++)
                board[1][jj] = ' '; // Reset ô hiện tại thành khoảng trắng

            i++;

            draw();
            _sleep(200);
        }
    }
    return removed;
}

// Kiểm tra game có kết thúc hay chưa.
// Ý tưởng:
// - Sau khi block cũ chạm đáy / chạm block khác, game sẽ spawn block mới.
// - Nếu block mới vừa spawn ra mà đã không thể đặt tại vị trí hiện tại,
//   nghĩa là vùng spawn đã bị chiếm.
// - Khi vùng spawn bị chiếm, người chơi không còn chỗ để tiếp tục.
// - Vì vậy game over.
// canMove(0, 0) nghĩa là:
// - không di chuyển sang trái/phải
// - không di chuyển xuống
// - chỉ kiểm tra block hiện tại có hợp lệ ở vị trí hiện tại không
bool isGameOver(const Blocks& currentBlock)
{
    return !currentBlock.canMove(0, 0);
}

// Hiển thị màn hình Game Over và hỏi người chơi muốn làm gì tiếp theo.
//
// Trả về:
// - true  nếu người chơi chọn R/r để restart
// - false nếu người chơi chọn Q/q để quit
bool showGameOverScreen()
{
    // Vẽ lại board lần cuối để người chơi thấy trạng thái lúc thua
    draw();

    int timePlayed = (int)difftime(time(0), gameStartTime);
    double piecesPerSecond = 0;

    if (timePlayed > 0)
        piecesPerSecond = (double)totalPiecesPlaced / timePlayed;

    cout << endl;
    cout << "==============================" << endl;
    cout << "         GAME OVER!           " << endl;
    cout << "==============================" << endl;

    // Hiển thị điểm cuối cùng trước khi reset hoặc thoát
    cout << "   Final Score     : " << score << endl;
    cout << "   Lines Cleared   : " << totalLinesCleared << endl;
    cout << "   Level Reached   : " << level << endl;
    cout << "   Pieces Placed   : " << totalPiecesPlaced << endl;
    cout << "   Time Played     : " << timePlayed << " sec" << endl;
    cout << "   Pieces / Second : " << piecesPerSecond << endl;

    cout << "------------------------------" << endl;
    cout << "   [R] Restart Game           " << endl;
    cout << "   [Q] Quit Game              " << endl;
    cout << "==============================" << endl;

    char choice;

    // Lặp cho đến khi người chơi nhập đúng phím hợp lệ.
    //
    // Các phím hợp lệ:
    // - R/r: chơi lại
    // - Q/q: thoát game
    //
    // Những phím khác sẽ bị bỏ qua.
    do
    {
        choice = getch();
    }
    while (
        choice != 'r' &&
        choice != 'R' &&
        choice != 'q' &&
        choice != 'Q'
    );

    // Nếu người chơi chọn R/r thì trả về true để main() reset game.
    // Nếu chọn Q/q thì trả về false để main() break khỏi game loop.
    return choice == 'r' || choice == 'R';
}

// Reset toàn bộ trạng thái cần thiết để bắt đầu lại game.
//
// Lưu ý:
// - initBoard() chỉ reset phần board.
// - resetGame() reset cả board, điểm, tốc độ và block hiện tại.
// Vì vậy phần restart nên gọi resetGame(), không chỉ gọi initBoard().
void resetGame(Blocks& currentBlock, char blocks[][4][4])
{
    // Xóa toàn bộ board cũ và dựng lại tường + vùng chơi trống
    initBoard();
    // Reset điểm về ban đầu
    score = 0;
    // Reset level
    level = 1;
    // Reset tốc độ rơi về ban đầu
    speed = 500;
    // Reset line cleared
    totalLinesCleared = 0;
    // reset pieces placed
    totalPiecesPlaced = 0;
    // reset start time
    gameStartTime = time(0);
    // Đưa block hiện tại về vị trí spawn mặc định
    currentBlock.setPosition(5, 0);
    // Chọn ngẫu nhiên loại block mới
    blockType = rand() % 7;
    // Gán hình dạng block mới cho currentBlock
    currentBlock.spawn(blocks, blockType);
}

int main()
{
    srand(time(0));
     // Doi tuong quan ly khoi dang roi
    Blocks currentBlock;
    // start game
    resetGame(currentBlock, blocks);

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
            totalPiecesPlaced++;

            int removed = removeLine();

            if (removed >= 1)
            {
                totalLinesCleared += removed;
                addScore(removed);
                updateLevel();
            }

            currentBlock.setPosition(5, 0);
            blockType = rand() % 7;
            currentBlock.spawn(blocks, blockType);

            if (isGameOver(currentBlock))
            {
                if (!showGameOverScreen())
                    break;

                resetGame(currentBlock, blocks);
            }
        }

        currentBlock.toBoard();
        draw();
        _sleep(speed);
    }

    return 0;
}
