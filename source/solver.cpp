#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

const string GAME_DIR = "..\\sudokuFiles\\";
const string EXT = ".sudoku";
const int ROWS = 9;
const int COLS = 9;

int main(){
    cout << "\nSUDOKU SOLVER\n\n";

    string fileName;
    int sudokuBoard[ROWS][COLS];
    void read(string& fileName, int sudokuBoard[][COLS]);
    void printBoard(int sudokuBoard[][COLS]);
    void solve(int sudokuBoard[][COLS]);

    cout << "What game do you want to solve?\n";
    for (const auto& entry : fs::directory_iterator(GAME_DIR)){
        fs::path path(entry.path());
        if (path.extension() == EXT) cout << path.stem() << endl;
    }
    cout << "Filename: ";
    cin >> fileName;
    cout << endl;

    read(fileName, sudokuBoard);
    cout << fileName << " Unsolved Board\n";
    printBoard(sudokuBoard);

    solve(sudokuBoard);

    cout << fileName << " Solved Board\n";
    printBoard(sudokuBoard);

    return 0;
}

void read(string& fileName, int sudokuBoard[][COLS]){
    ifstream file(GAME_DIR + fileName + EXT);
    string line;

    if (file.is_open())
        for (int row = 0; row < ROWS; row++){
            file >> line;
            for (int col = 0; col < COLS; col++)
                sudokuBoard[row][col] = line[col] - '0';
        }

    return;
}

void solve(int sudokuBoard[][COLS]){
    bool notesBoard[ROWS][COLS][9];

    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            if (sudokuBoard[row][col] != 0) continue;
            for (int lineCheck = 0; lineCheck < ROWS; lineCheck++){
                if (sudokuBoard[lineCheck][col] != 0)
                    notesBoard[row][col][sudokuBoard[lineCheck][col]-1] = 1;
                if (sudokuBoard[row][lineCheck] != 0)
                    notesBoard[row][col][sudokuBoard[row][lineCheck]-1] = 1;
            }
        }
    }

    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            for (int num = 0; num < 9; num++)
                notesBoard[row][col][num] = (notesBoard[row][col][num] == 1) ? 0 : 1;

    for (int i = 0; i < 9; i++){
        cout << "  " << notesBoard[0][2][i] * (i+1);
    }

    return;
}

void printBoard(int sudokuBoard[][COLS]){
    for (double row = 0; row < ROWS; row++){
        if (row / 3 == int(row / 3)){
            for (int i = 0; i < COLS+4; i++) cout << "---";
            cout << endl;
        }
        for (double col = 0; col < COLS; col++){
            if (col / 3 == int(col / 3)) cout << " | ";
            if (sudokuBoard[(int)row][(int)col] == 0) cout << "   ";
            else cout << " " << sudokuBoard[(int)row][(int)col] << " ";
            if (col == COLS-1) cout << " | ";
        }
        cout << endl;
        if (row == ROWS-1){
            for (int i = 0; i < COLS+4; i++) cout << "---";
            cout << endl << endl;
        }
    }

    return;
}