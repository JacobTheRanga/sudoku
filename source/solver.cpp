#include <iostream>
#include <fstream>
#include <filesystem>
#include "solver.h"

using namespace std;
namespace fs = filesystem;

int main(){
    cout << "\nSUDOKU SOLVER\n\n";

    string fileName;
    int newBoard[ROWS][COLS];

    fileName = filePath();
    read(fileName, newBoard);
    Sudoku board(newBoard);
    
    cout << fileName << " Unsolved Board\n";
    board.printBoard();

    board.solve();

    board.printNotes();

    cout << fileName << " Solved Board\n";
    board.printBoard();

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

void read(string& fileName, int board[][COLS]){
    ifstream file(GAME_DIR + fileName + EXT);
    string line;

    if (file.is_open())
        for (int row = 0; row < ROWS; row++){
            file >> line;
            for (int col = 0; col < COLS; col++)
                board[row][col] = line[col] - '0';
        }

    return;
}

Sudoku::Sudoku(int newBoard[ROWS][COLS]){
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            board[row][col] = newBoard[row][col];
}

void Sudoku::invert(){
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++)
            for (int num = 0; num < 9; num++)
                notes[row][col][num] = (board[row][col] == 0) ? 1 : 0;

    return;
}

void Sudoku::check(){
    int table[2];
    int gridCheck[2];
    int grid[2];

    for (table[0] = 0; table[0] < ROWS; table[0]++)
        for (table[1] = 0; table[1] < COLS; table[1]++){
            if (board[table[0]][table[1]] != 0) continue;

            for (int lineCheck = 0; lineCheck < ROWS; lineCheck++){

                if (board[lineCheck][table[1]] != 0)
                    notes[table[0]][table[1]][board[lineCheck][table[1]]-1] = 0;

                if (board[table[0]][lineCheck] != 0)
                    notes[table[0]][table[1]][board[table[0]][lineCheck]-1] = 0;
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
                    if (board[gridCheck[0]][gridCheck[1]] == 0) continue;
                    notes[table[0]][table[1]][board[gridCheck[0]][gridCheck[1]]-1] = 0;
                }
        }

    return;
}

bool Sudoku::fill(){
    int temp;
    bool changed = false;
    for (int row = 0; row < ROWS; row++)
        for (int col = 0; col < COLS; col++){
            temp = 0;
            if (board[row][col] != 0) continue;
            for (int num = 0; num < 9; num++){
                if (notes[row][col][num] == 0) continue;
                if (temp != 0){
                    temp = 0;
                    break;
                };
                temp = notes[row][col][num] * (num+1);
            }
            if (temp == 0) continue;
            board[row][col] = temp;
            notes[row][col][temp-1] = 0;
            changed = true;
        }
    return changed;
}


void Sudoku::solve(){
    bool changed;

    invert();

    do{
        check();
        changed = fill();
    }
    while (changed);

    return;
}

void Sudoku::printNotes(){
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            cout << "{";
            for (int num = 0; num < 9; num++){
                if (notes[row][col][num] == 0) continue;
                printf(" %d", notes[row][col][num] * (num+1));
            }
            cout << " }, ";
        }
        cout << endl;
    }

    return;
}

void Sudoku::printBoard(){
    for (int row = 0; row < ROWS; row++){
        if ((double)row / 3 == int(row / 3)){
            for (int i = 0; i < COLS+4; i++) cout << "---";
            cout << endl;
        }
        for (int col = 0; col < COLS; col++){
            if ((double)col / 3 == int(col / 3)) cout << " | ";
            if (board[row][col] == 0) cout << "   ";
            else cout << " " << board[row][col] << " ";
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