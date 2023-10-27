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
    bool notesBoard[ROWS][COLS][9];
    string filePath(void);
    void read(string& fileName, int sudokuBoard[][COLS]);
    void invert(bool notesBoard[][COLS][9]);
    void possibleOutcomes(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]);
    void printBoard(int sudokuBoard[][COLS]);

    fileName = filePath();
    read(fileName, sudokuBoard);
    cout << fileName << " Unsolved Board\n";
    printBoard(sudokuBoard);

    invert(notesBoard);
    possibleOutcomes(sudokuBoard, notesBoard);

    cout << fileName << " Solved Board\n";
    printBoard(sudokuBoard);

    return 0;
}

string filePath(){
    string fileName;

    cout << "What game do you want to solve?\n";
    for (const auto& entry : fs::directory_iterator(GAME_DIR)){
        fs::path path(entry.path());
        if (path.extension() == EXT) cout << path.stem() << endl;
    }
    cout << "Filename: ";
    cin >> fileName;
    cout << endl;
    return fileName;
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

void invert(bool notesBoard[][COLS][9]){
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            for (int num = 0; num < 9; num++)
                notesBoard[row][col][num] = (notesBoard[row][col][num] == 1) ? 0 : 1;
    return;
}

void possibleOutcomes(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]){
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++){
            if (sudokuBoard[row][col] != 0) continue;
            for (int lineCheck = 0; lineCheck < ROWS; lineCheck++){
                if (sudokuBoard[lineCheck][col] != 0)
                    notesBoard[row][col][sudokuBoard[lineCheck][col]-1] = 0;
                if (sudokuBoard[row][lineCheck] != 0)
                    notesBoard[row][col][sudokuBoard[row][lineCheck]-1] = 0;
            }
            int realRow;
            int realCol;
            for (int gridRow = 0; gridRow < 3; gridRow++)
                for (int gridCol = 0; gridCol < 3; gridCol++){
                    if ((double)row / 3.0  == row / 3)
                        realRow = row + gridRow;
                    if ((double)row / 3.0 - row / 3 == 2.0/3.0)
                        realRow = row - gridRow;
                    if ((double)row / 3.0 - row / 3 == 1.0/3.0){
                        if (gridRow == 0) realRow = row;
                        if (gridRow == 1) realRow = row - 1;
                        if (gridRow == 2) realRow = row + 1;
                    }
                    if ((double)col / 3.0  == col / 3)
                        realCol = col + gridCol;
                    if ((double)col / 3.0 - col / 3 == 2.0/3.0)
                        realCol = col - gridCol;
                    if ((double)row / 3.0 - row / 3 == 1.0/3.0){
                        if (gridCol == 0) realCol = col;
                        if (gridCol == 1) realCol = col - 1;
                        if (gridCol == 2) realCol = col + 1;
                    }
                    if (sudokuBoard[realRow][realCol] != 0)
                        notesBoard[row][col][sudokuBoard[realRow][realCol]-1] = 0;
                }
        }

    return;
}

void printBoard(int sudokuBoard[][COLS]){
    for (int row = 0; row < ROWS; row++){
        if ((double)row / 3 == int(row / 3)){
            for (int i = 0; i < COLS+4; i++) cout << "---";
            cout << endl;
        }
        for (int col = 0; col < COLS; col++){
            if ((double)col / 3 == int(col / 3)) cout << " | ";
            if (sudokuBoard[row][col] == 0) cout << "   ";
            else cout << " " << sudokuBoard[row][col] << " ";
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