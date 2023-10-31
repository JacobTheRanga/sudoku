#include <iostream>

const std::string GAME_DIR = "..\\sudokuFiles\\";
const std::string EXT = ".sudoku";
const int ROWS = 9;
const int COLS = 9;

std::string filePath(void);
void read(std::string &fileName, int sudokuBoard[][COLS]);

class Sudoku{
    int board[ROWS][COLS];
    bool notes[ROWS][COLS][9];

    public:
    Sudoku(int newBoard[ROWS][COLS]);
    void invert(void);
    void check(void);
    bool fill(void);
    void solve(void);
    void printNotes(void);
    void printBoard(void);

};