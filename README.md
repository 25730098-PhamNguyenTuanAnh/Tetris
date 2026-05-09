# Tetris

A terminal-based Tetris game written in C++, built as the final project for class **SS004.F21.CN1.CNTT** at the University of Information Technology (UIT), Vietnam National University Ho Chi Minh City.

## Contributors

| No. | Full Name | Student ID | Email | GitHub |
|-----|-----------|------------|-------|--------|
| 1 | Pham Nguyen Tuan Anh (Leader) | 25730098 | 25730098@ms.uit.edu.vn | [25730098-PhamNguyenTuanAnh](https://github.com/25730098-PhamNguyenTuanAnh) |
| 2 | Ho Dac Minh Duc | 25730107 | 25730107@ms.uit.edu.vn | [25730107-HoDacMinhDuc](https://github.com/25730107-HoDacMinhDuc) |
| 3 | Huynh An Loc Son | 25730140 | 25730140@ms.uit.edu.vn | [25730140huynhanlocson](https://github.com/25730140huynhanlocson) |
| 4 | Phan Ngoc Tu Quyen | 25730139 | 25730139@ms.uit.edu.vn | [UIT-25730139-PhanNgocTuQuyen](https://github.com/UIT-25730139-PhanNgocTuQuyen) |
| 5 | Nguyen Bao Anh | 25730097 | 25730097@ms.uit.edu.vn | [anh25730097](https://github.com/anh25730097) |

**Project Board:** [View on GitHub](https://github.com/users/25730098-PhamNguyenTuanAnh/projects/1) used for tracking issues and planning

## About the Game

Tetris is one of the most iconic video games ever created. Originally developed in 1984 in the Soviet Union, its name combines *tetra* (Greek for "four," since every piece is made of four squares) with *tennis*, the creator's favourite sport.

This project recreates the classic Tetris experience in a terminal environment. Players control seven types of falling tetrominoes (I, O, T, S, Z, L, J), arranging them on a 15x20 grid to complete and clear horizontal lines. The game features a main menu, pause functionality, a scoring system, level progression with increasing speed, game-over statistics, and persistent high score tracking.

## Features

- 7 standard tetrominoes with rotation support
- Scoring system: 100 / 300 / 500 / 800 points for 1 / 2 / 3 / 4 lines cleared
- Level progression: speed increases every 10 lines cleared
- Next-piece preview
- Pause menu with resume, restart, and quit options
- Game-over screen with session statistics (lines cleared, level reached, pieces placed, time played, pieces per second)
- High score persistence via `highscore.txt`

## Controls

| Key | Action |
|-----|--------|
| `A` | Move left |
| `D` | Move right |
| `W` | Rotate piece (in-game) / Navigate up (in menus) |
| `S` | Navigate down (in menus) |
| `X` | Soft drop (faster fall) |
| `P` | Pause / unpause |
| `R` | Restart after game over |
| `Q` | Quit |
| `Enter` | Confirm menu selection |

## Build and Run

**Requirements:** Windows with a C++ compiler (e.g., `g++` from MinGW or MSYS2). The game uses `<conio.h>` for real-time keyboard input, so it is designed for Windows terminals.

```bash
git clone https://github.com/25730098-PhamNguyenTuanAnh/Tetris.git
cd Tetris
g++ main.cpp -o tetris.exe
./tetris.exe
```
