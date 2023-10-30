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
    void invert(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]);
    void check(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]);
    bool fill(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]);
    void solve(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]);
    void printNotes(bool notesBoard[][COLS][9]);
    void printBoard(int sudokuBoard[][COLS]);

    fileName = filePath();
    read(fileName, sudokuBoard);
    cout << fileName << " Unsolved Board\n";
    printBoard(sudokuBoard);

    solve(sudokuBoard, notesBoard);

    printNotes(notesBoard);

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

void invert(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]){
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            for (int num = 0; num < 9; num++)
                notesBoard[row][col][num] = (sudokuBoard[row][col] == 0) ? 1 : 0;

    return;
}

void check(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]){
    int table[2];
    int gridCheck[2];
    int grid[2];

    for (table[0] = 0; table[0] < ROWS; table[0]++)
        for (table[1] = 0; table[1] < COLS; table[1]++){
            if (sudokuBoard[table[0]][table[1]] != 0) continue;

            for (int lineCheck = 0; lineCheck < ROWS; lineCheck++){

                if (sudokuBoard[lineCheck][table[1]] != 0)
                    notesBoard[table[0]][table[1]][sudokuBoard[lineCheck][table[1]]-1] = 0;

                if (sudokuBoard[table[0]][lineCheck] != 0)
                    notesBoard[table[0]][table[1]][sudokuBoard[table[0]][lineCheck]-1] = 0;
            }

            for (int i = 0; i < 2; i++){
                if (table[i] / 3.0  == table[i] / 3)
                    grid[i] = table[i];
                else if (table[i] / 3.0 - table[i] / 3 > 0.6)
                    grid[i] = table[i] - 2;
                else grid[i] = table[i] - 1;
            }
            for (gridCheck[0] = grid[0]; gridCheck[0] < grid[0]+3; gridCheck[0]++)
                for (gridCheck[1] = grid[1]; gridCheck[1] < grid[1]+3; gridCheck[1]++){
                    if (sudokuBoard[gridCheck[0]][gridCheck[1]] == 0) continue;
                    notesBoard[table[0]][table[1]][sudokuBoard[gridCheck[0]][gridCheck[1]]-1] = 0;
                }
        }

    return;
}

bool fill(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]){
    int temp;
    bool changed = false;
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++){
            temp = 0;
            if (sudokuBoard[row][col] != 0) continue;
            for (int num = 0; num < 9; num++){
                if (notesBoard[row][col][num] == 0) continue;
                if (temp != 0){
                    temp = 0;
                    break;
                };
                temp = notesBoard[row][col][num] * (num+1);
            }
            if (temp == 0) continue;
            sudokuBoard[row][col] = temp;
            notesBoard[row][col][temp-1] = 0;
            changed = true;
        }
    return changed;
}

void solve(int sudokuBoard[][COLS], bool notesBoard[][COLS][9]){
    bool changed;

    invert(sudokuBoard, notesBoard);

    do{
        check(sudokuBoard, notesBoard);
        changed = fill(sudokuBoard, notesBoard);
    }
    while (changed);

    return;
}

void printNotes(bool notesBoard[][COLS][9]){
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            cout << "{";
            for (int num = 0; num < 9; num++){
                if (notesBoard[row][col][num] == 0) continue;
                printf(" %d", notesBoard[row][col][num] * (num+1));
            }
            cout << " }, ";
        }
        cout << endl;
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