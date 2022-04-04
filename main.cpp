#include <iostream>
#include <cstdint>
#include "stack.h"
#define IS_FILLED_IN(r,c) ((board[r][c] & FILLED_IN) != 0)
#define MARK_INVALID(r,c,i) (board[r][c] &= (uint16_t)~(uint16_t)(VALID_START >> (uint16_t)(i)))

using namespace std;

bool findBest(uint16_t board[9][9]);
void solveBoard(uint16_t board[9][9]);

const uint16_t    FILLED_IN = 0x8000;
const uint16_t    VALID_MASK = 0x1ff0;
const uint16_t    VALUE_MASK = 0x000f;
const uint16_t    VALID_START = 0x2000;
Stack <int> s;

int main() {
    uint16_t board[9][9];
    char ch;
    for(int i =0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> ch;
            if(ch=='.'){
                board[i][j] = 0;
            }
            else{
                board[i][j] = FILLED_IN | (ch - '0');
            }
        }
    }
    solveBoard(board);

    return 0;
}

bool findBest(uint16_t board[9][9]){
   for (int r =0; r < 9; r++) {
       for (int c = 0; c < 9; c++) {
           if(!IS_FILLED_IN(r,c)){
                board[r][c] = VALID_MASK;
           }
       }
   }
    for (int r =0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (IS_FILLED_IN(r, c)) {
                for (int i = 0; i < 9; i++) {
                    if (!IS_FILLED_IN(i, c)) {
                        MARK_INVALID(i, c, board[r][c] & VALUE_MASK);
                    }
                }
                for (int j = 0; j < 9; j++) {
                    if (!IS_FILLED_IN(r, j)) {
                        MARK_INVALID(r, j, board[r][c] & VALUE_MASK);
                    }
                }

                int r2 = (r / 3) * 3;
                int c2 = (c / 3) * 3;

                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        if (!IS_FILLED_IN(k+r2, l+c2)) {
                            MARK_INVALID(k+r2, l+c2, board[r][c] & VALUE_MASK);
                        }
                    }
                }

            }
        }
    }


    int low = 10;
    int i_best;
    int j_best;
    for (int r =0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            //Count 1-bits in valid choices for board[i][j]
            if(!IS_FILLED_IN(r,c)){
                int count =0;
                int tmp = (board[r][c] & VALID_MASK);
                while(tmp != 0){
                    count++;
                    tmp &= tmp -1;
                }

            if(count < low){
                low = count;
                i_best = r;
                j_best = c;
            }
            }
        }
    }

    if(low == 10){
        return false;
    }

    //MARK board[i_best,j_best] as filled in
    board[i_best][j_best] = board[i_best][j_best] | FILLED_IN;
    //Push (i_best,j_best) onto the stack
    //storing location in the board as the following in the stack
    s.push(9*i_best+j_best);
    return true;

}

void solveBoard(uint16_t board[9][9]) {
    findBest(board);
    while (true) {
        int i = s.peek() / 9;
        int j = s.peek() % 9;
        int n;
        for (n = 1; n <= 9; n++) {
            board[i][j] = (board[i][j] & ~VALUE_MASK) | n;
            if ((board[i][j] & (VALID_START >> n)) != 0) {
                MARK_INVALID(i,j,n);
                break;
            }
        }
            if (n == 10) {
                board[i][j] &= ~FILLED_IN;
                s.pop();
                if (s.isEmpty()) {
                    cout << "Puzzle has no solution" << endl;
                    return;
                }
                continue;
            }
            if (!findBest(board)) {
                break;
            }
        }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << (board[i][j] & VALUE_MASK);
            }
            cout << endl;
        }
    }