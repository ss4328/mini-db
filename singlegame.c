//
// Created by Shivansh Suhane on 2019-09-07.
//

#ifndef SINGLEC4GAME_GAME_H
#define SINGLEC4GAME_GAME_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* emptyString = " ";


class game {

public:
    int boardLength = 7;
    char* board[7][7];
    int p1,p2;
    bool completed=false;
    int lastMoved;
    char* nextpiece;
    int movesPlayed;

    // prints 0 for child, 1 for parent
//    int returnPlayerWon(){
//
//    }


//gamemoves
    void playRandomMove(char* piece){
        int col = rand() % 7;
        if(playMoveOnCol(col, piece)){
            printf("Move played \n");
        }
        else{

            int tries = 6;
            for(tries; tries>0;tries--){
                printf("Position unavailable. Trying next column. \n");
                if(col==6){col=0;}
                else{col++;}
                if(playMoveOnCol(col,piece)){
                    printf("Move now played on col %d \n", col+1);
                    break;
                }
            }
        }

    }

    void playBestMove(char *board){

    }

    //inserts a piece in a give column, returns false if whole column is filled up
    bool playMoveOnCol(int colNumber, char* piece){
        for(int row=boardLength-1;row>=0; row--){
            if(positionAvailable(board[row][colNumber])){
                board[row][colNumber] = piece;
                return true;
            }
        }
        return false;
    }
    int findBestMoveCol(char* board){

    }

    //helpers
    bool positionAvailable(char* position){
        if (strcmp(position, emptyString)==0){
            return true;
        }
        else return false;

    }


    void setUpBoard() {
    printf("setting up board \n");
        for (int i = 0; i < boardLength; i++) {
            for (int j = 0; j < boardLength; j++) {
                board[i][j] = " ";
            }
        }
    movesPlayed =0;
    }

    void printBoard(){
        int row, col;

        system("clear");

        puts("\n BOARD \n");
        for(row = 0; row < boardLength; row++){
            for(col = 0; col < boardLength; col++){
                printf("| %s ",  board[row][col]);
            }
            puts("|");
            puts("-----------------------------");

        }
        puts("  1   2   3   4   5   6   7\n");

    }

    int checkWin(){
        if(horizontalCheck() || verticalCheck() || diagonalCheck()){
            return 1;
        }
        else{
            return 0;
        }

    }

    int checkFour(int a, int b, int c, int d){
        if(board[a] == board[b] && board[b] == board[c] && board[c] == board[d] && **board[a] != ' '){
            return 1;
        }
        else{
            return 0;
        }
    }

    int horizontalCheck(){
        int row, col, index;
        const int WIDTH = 1;

        for(row = 0; row < boardLength; row++){
            for(col = 0; col < boardLength - 3; col++){
                index = boardLength * row + col;
                if(checkFour(index, index + WIDTH, index + WIDTH * 2, index + WIDTH * 3)){
                    return 1;
                }
            }
        }
        return 0;

    }
    int verticalCheck(){
        int row, col, index;
        const int HEIGHT = 7;

        for(row = 0; row < boardLength - 3; row++){
            for(col = 0; col < boardLength; col++){
                index = boardLength * row + col;
                if(checkFour(index, index + HEIGHT, index + HEIGHT * 2, index + HEIGHT * 3)){
                    return 1;
                }
            }
        }
        return 0;

    }
    int diagonalCheck(){
        int row, col, index, count = 0;
        const int DIAG_RGT = 6, DIAG_LFT = 8;

        for(row = 0; row < boardLength - 3; row++){
            for(col = 0; col < boardLength; col++){
                index = boardLength * row + col;
                if(count <= 3 && checkFour(index, index + DIAG_LFT, index + DIAG_LFT * 2, index + DIAG_LFT * 3) || count >= 3 && checkFour(index, index + DIAG_RGT, index + DIAG_RGT * 2, index + DIAG_RGT * 3)){
                    return 1;
                }
                count++;
            }
            count = 0;
        }
        return 0;

    }


};

#endif //SINGLEC4GAME_GAME_H
q