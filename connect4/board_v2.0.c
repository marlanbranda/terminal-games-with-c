///
/// NEW SECOND VERSION OF THE CONNECT FOUR. NOW ALL PROGRAM BASED ON THE STRUCT NAMED BOARD.
/// ALL THE FUNCTIONS MAKES MANIPULATION ON IT.
/// BECAUSE THEY ONE BY ONE MAKES MANIPULATION ON SAME OBJECT IT IS MUCH MORE EASY TO UNDERSTAND THE CODE
/// AND ALSO IT IS HOPEFULLY EASIER TO UPDATE THE CODES 
///

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define GAME_NAME "CONNECT FOUR"
#define ROWS 6
#define COLS 7
#define PL1 1
#define PL2 8


typedef struct Board{
    int boardMat[ROWS][COLS];
    int situation;           
    int valid_move_left;
    int is_wrong_inp;
    char wrong_input[100];
    int turn;
}Board;



Board *initialize_board();
void print_board(Board *boardObj);
void make_move(Board *boardObj);
void check_winner(Board *boardObj);
void test_function(Board *boardObj);

void win_check_horizontal(Board *boardObj);
void win_check_vertical(Board *boardObj);    
void win_check_rdiagon(Board *boardObj);
void win_check_ldiagon(Board *boardObj);
int check_counter(int counter);



int main(){

    Board *boardObj = initialize_board();
    while(boardObj->situation == 0){
        print_board(boardObj);
        // test_function(boardObj); // comment out the make_move func to test 
        make_move(boardObj);
        check_winner(boardObj);
    }
    print_board(boardObj);
    free(boardObj);
    return 0;
}


Board *initialize_board(){

    Board *boardObj = malloc(sizeof(Board));
    
    *boardObj = (Board) {
        .boardMat = {0}, // Set all elements to 0
        .situation = 0,
        .turn = 0,
        .valid_move_left = 1,
        .is_wrong_inp = 0,
        .wrong_input = ""
    };

    return boardObj;
}


void print_board(Board* boardObj){

    printf("\033[2J"); // this clears the screen 
    
    // print the error if there is error
    if(boardObj->is_wrong_inp){
        printf("ERROR: %s \n", boardObj->wrong_input);       
        boardObj->is_wrong_inp = 0;
    }

    // if draw prints out draw
    if (boardObj->situation == 3){
        printf("game ended in draw");                         
    }

    // if there is winner declares winner 
    else if (boardObj->situation == 1 || boardObj->situation == 2){
        printf("player%d is the winner!!! \n \n", boardObj->situation);  
    }

    // game headers
    printf("*************************");
    printf("%s","CONNECT FOUR");
    printf("*************************");
    printf("\n");
    printf("player1 : X || player2 : O \n \n \n");       
    
    //prints the boardMat to terminal
    for (int i=0; i<ROWS; i++){                          
        printf("\t\t"); 
        for(int j=0; j<COLS; j++){
            switch (boardObj->boardMat[i][j]){
            case 1:
                printf("X ");
                break;
            case 8:
                printf("O ");
                break;
            case 0:
                printf("- ");
                break;                
            }
        }
        
        printf("\n");
    }
    
    // just print line to seperate game board
    printf("\n------------------------------------------------------\n");
    
    // prints the turn
    if (boardObj->situation == 0){
        printf("turn : %d ", boardObj->turn); 
    }
}


void make_move(Board* boardObj){   

    int selected_col;
    int check_if_int;
    int player; 

    // deciding whose turn
    if (boardObj->turn % 2 == 0)   {player = PL1;}
    else                           {player = PL2;}

    // take the user input
    printf("player %d, select your move\n", player);
    // scanf returns zero if alphabetic char is given
    check_if_int = scanf("%d", &selected_col); 
    // difference between humancounting and computer counting
    selected_col--; 
    
    if (check_if_int != 1){
        strcpy(boardObj->wrong_input, "input is not integer"); 
        boardObj->is_wrong_inp = 1;
        fflush(stdin);
    }
    else{
        if (selected_col < 0 || selected_col >= COLS){
            strcpy(boardObj->wrong_input, "input is not in the range of board"); 
            boardObj->is_wrong_inp = 1;
            fflush(stdin);
        }
        else{
            if (boardObj->boardMat[0][selected_col] != 0){
                strcpy(boardObj->wrong_input, "that column is full");
                boardObj->is_wrong_inp = 1;
                fflush(stdin);
            }
            else{
                // emp_row assigned to bottom row
                int emp_row = ROWS - 1;
                // find the non-zero row in given column
                // assign the one above if non-zero found
                for (int i=0; i<ROWS; i++){
                    if (boardObj->boardMat[i][selected_col] != 0){
                        emp_row = i - 1;
                        break;
                    }
                }
                // assign the value of player according to turn 
                boardObj->boardMat[emp_row][selected_col] = player;
                // increase turn, effectively changes the player
                boardObj->turn++ ; 
            }
        }
    }

    
}



void check_winner(Board* boardObj){

    if(boardObj->situation == 0){
        win_check_horizontal(boardObj);
    }
    if(boardObj->situation == 0){
        win_check_vertical(boardObj);
    }
    if(boardObj->situation == 0){
        win_check_rdiagon(boardObj);
    }
    if(boardObj->situation == 0){
        win_check_ldiagon(boardObj);
    }
}

int check_counter(int counter){
   
   // program check winner according to sum of 4 neighbouring elements
   // for player1 we add 1 and for player 2 we add 8 to matrix
   // thus when 4 of them put consecutively in matrix we either get 4 or 32
    switch(counter){
        case 32:
            return 2; //winner is PL2
        case 4:
            return 1; //winner is PL1
        default:
            return 0; // no result 
    }
    return 0;
}


void win_check_horizontal(Board* boardObj){

    int counter = 0;
    // create an array whic has length of columns
    int boardLine[COLS] = {}; 
    // program copy the each row into boardLine
    for (int i=0; i<ROWS; i++){
        for (int j= 0; j < COLS; j++){
            boardLine[j] = boardObj->boardMat[i][j]; 
        }
        for (int k = 0; k <= COLS - 4; k++){
            // according to lenght of columns this loop looks for the 4 neighbouring elements in loop
            counter = boardLine[k] + boardLine[k+1] + boardLine[k+2] + boardLine[k+3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2){
                boardObj->situation = check_counter(counter);
            }
        }
    } 
}

void win_check_vertical(Board* boardObj){

    int counter = 0;
    // create an array whic has length of rows
    int boardLine[ROWS] = {};
    // program copy the each column into boardLine
    for (int i=0; i<COLS; i++){
        for (int j= 0; j < ROWS; j++){
            boardLine[j] = boardObj->boardMat[j][i];
        }
    
        for (int k = 0; k <= ROWS - 4; k++){
            // according to lenght of rows this loop looks for the 4 neighbouring elements in loop
            counter = boardLine[k] + boardLine[k+1] + boardLine[k+2] + boardLine[k+3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2){
                boardObj->situation = check_counter(counter);
            }
        }
    }
}
    
void win_check_rdiagon(Board* boardObj){

    int counter = 0;
    int boardDiagolLine[4] = {};
    // starting from the fourth row, we go down
    for (int i = 3; i <= ROWS - 1; i++){
        // starting from the first column, we go right
        for (int j = 0; j < COLS - 3; j++){
            boardDiagolLine[0] = boardObj->boardMat[i  ][j  ]; // the element we chose
            boardDiagolLine[1] = boardObj->boardMat[i-1][j+1]; // one up one right 
            boardDiagolLine[2] = boardObj->boardMat[i-2][j+2]; // and so on.. 
            boardDiagolLine[3] = boardObj->boardMat[i-3][j+3]; // ..
            
            counter = boardDiagolLine[0] + boardDiagolLine[1] + boardDiagolLine[2] + boardDiagolLine[3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2){
                boardObj->situation = check_counter(counter);
            }

        }            
    }
}

void win_check_ldiagon(Board* boardObj){

    int counter = 0;
    int boardDiagolLine[4] = {};
    // starting from the fourth row, we go down
    for (int i = 3; i <= ROWS - 1; i++){
        // starting from the last column, we go left
        for (int j = COLS - 1; j >= 3; j--){
            boardDiagolLine[0] = boardObj->boardMat[i  ][j  ]; // the element we chose
            boardDiagolLine[1] = boardObj->boardMat[i-1][j-1]; // one up one left
            boardDiagolLine[2] = boardObj->boardMat[i-2][j-2]; // and so on..
            boardDiagolLine[3] = boardObj->boardMat[i-3][j-3]; // ..
            
            counter = boardDiagolLine[0] + boardDiagolLine[1] + boardDiagolLine[2] + boardDiagolLine[3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2){
                boardObj->situation = check_counter(counter);
            }
        }            
    }
}


void test_function(Board *boardObj)
{
    // to be able to test the winner functions
    // it is way hard to design the board entering values one by one and time-consuming
    int testBoard[ROWS][COLS] = {
        {8, 8, 8, 0, 0, 8, 8},
        {1, 1, 1, 0, 0, 1, 1},
        {8, 8, 8, 0, 0, 8, 1},
        {1, 1, 1, 8, 1, 1, 8},
        {8, 8, 8, 1, 8, 8, 1},
        {1, 1, 1, 8, 1, 8, 1} 
    };

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            boardObj->boardMat[i][j] = testBoard[i][j];
        }
    }
}

