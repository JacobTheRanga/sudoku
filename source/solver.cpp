#include <iostream>
#include <fstream>
#include <filesystem>
#include "solver.hpp"

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

void Sudoku::initNotes(){
    if (board[realNum[0]][realNum[1]] == 0) return;
    notes[checkNum[0]][checkNum[1]][board[realNum[0]][realNum[1]]-1] = 0;

    return;
}

void Sudoku::unique(){
    for (int num = 0; num < 9; num++){
        if (notes[checkNum[0]][checkNum[1]][num] ==
            notes[realNum[0]][realNum[1]][num])
            continue;
        
    }

    return;
}

void Sudoku::check(void (Sudoku::*func)(void)){
    int gridCheck[2];
    for (checkNum[0] = 0; checkNum[0] < ROWS; checkNum[0]++)
        for (checkNum[1] = 0; checkNum[1] < COLS; checkNum[1]++){
            for (int i = 0; i < 2; i++){
                for (realNum[i] = 0; realNum[i] < ROWS; realNum[i]++){
                    if (i == 0) realNum[1] = checkNum[1];
                    else realNum[0] = checkNum[0];
                    (this->*func)();
                }
                if (checkNum[i] / 3.0  == checkNum[i] / 3)
                    gridCheck[i] = checkNum[i];
                else if (checkNum[i] / 3.0 - checkNum[i] / 3 > 0.6)
                    gridCheck[i] = checkNum[i] - 2;
                else gridCheck[i] = checkNum[i] - 1;
            }
            for (realNum[0] = gridCheck[0]; realNum[0] < gridCheck[0]+3; realNum[0]++)
                for (realNum[1] = gridCheck[1]; realNum[1] < gridCheck[1]+3; realNum[1]++){
                    (this->*func)();
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
    invert();

    do{
        check(&initNotes);
        // check(&unique);
    }
    while (fill());

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