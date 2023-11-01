#include <iostream>

const std::string GAME_DIR = "..\\sudokuFiles\\";
const std::string EXT = ".sudoku";
const int ROWS = 9;
const int COLS = 9;

std::string filePath(void);
void read(std::string &fileName, int sudokuBoard[][COLS]);

class Sudoku{
public:
    Sudoku(int newBoard[ROWS][COLS]);
    void printNotes(void);
    void printBoard(void);
    void solve(void);

private:
    int board[ROWS][COLS];
    bool notes[ROWS][COLS][9];
    int checkNum[2];
    int realNum[2];
    int total;
    int num;

    void invert(void);
    void initNotes(void);
    // void unique(void);
    void check(void (Sudoku::*func)(void));
    bool fill(void);
};