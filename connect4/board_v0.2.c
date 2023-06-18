#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define PL1 1
#define PL2 8


void print_board(int boardArr[ROWS][COLS]);
int make_move(int boardArr[ROWS][COLS], int player, int col); //returns 0 if error, returns 1 if succesful 
int check_input_range(int boardArr[ROWS][COLS], int col); // to check the if the input is in range of game board
int check_col(int boardArr[ROWS][COLS], int col); //check if the column is empty
int valid_move_left(int boardArr[ROWS][COLS]);
int check_winner(int boardArr[ROWS][COLS]);


int main()
{
    // create an empty board
    int boardObj[ROWS][COLS] = {0};
    int turn = 0;
    int player;
    int selected_col;
    int match_result = 0; // 1 if player 1 won, 2 if player 2 is won, 0 is indicates that there isn't winning situation

    do
    {
        print_board(boardObj);
        
        printf("turn:%d", turn);
        if (turn % 2 == 0)   {player = PL1;}
        else                 {player = PL2;}

        printf("player with number %d, select your move\n", player);
        scanf("%d", &selected_col);

        if (make_move(boardObj, player, selected_col) == 1 ) {turn++;};

        match_result = check_winner(boardObj); // zero of match_result is meaning to continue; not draw

        switch (match_result)
        {
        case 1:
            printf("player 1 wons");
        case 2:
            printf("player 2 won");
        }

    }while(valid_move_left(boardObj) == 1 && match_result != 1 && match_result != 2);

    if (valid_move_left(boardObj) == 0 && match_result == 0)
    {
        printf("game is finished in draw");
    }

    return 0;
}


void print_board(int boardArr[ROWS][COLS])
{
    printf("\n----- this is the current situation in board ----- \n\n"); //for clear terminal view
    for (int i=0; i<ROWS; i++)
    {
        printf("\t"); //for clear terminal view 
        for(int j=0; j<COLS; j++)
        {
            printf("%d ", boardArr[i][j]);
        }
        printf("\n");
    }
    printf("\n------------------------------------------------------\n");
}


int make_move(int boardArr[ROWS][COLS], int player, int col)
{   
    //returns 0 if error, returns 1 if succesfuls
    
    if(check_input_range(boardArr, col) == 1)
    {
        if (check_col(boardArr, col) == 1) 
        {
            //find the lowest empty one
            col--; // from humancounting to computer counting 
            int emp_row = ROWS - 1;
            for (int i=0; i<ROWS; i++)
            {
                if (boardArr[i][col] != 0)
                {
                    emp_row = i - 1; //computer starts counting from 0 !!!
                    break;
                }
            }

            boardArr[emp_row][col] = player; //change it
            return 1;
        }
    }
    else
    {
        return 0; //move wasn't made
    }
}


int check_col(int boardArr[ROWS][COLS], int col)
{
    col--; // from humancounting to computer counting 
    // test required !!!
    if (boardArr[0][col] == 0) // only checks for if the top one is empty
    {
        return 1; // returns 1 if move is possible 
    }

    else
    {
        printf("\n\nERROR: column you want to make move is full\n");
        return 0; // returns 0 if move is impossible
    }
}


int check_input_range(int boardArr[ROWS][COLS], int col)
{
    col--; // from humancounting to computer counting 
    if (col < COLS && col >= 0) 
    {
        return 1; // returns 1 if move is in range 
    }

    else
    {
        printf("\n\nERROR: your input is not in the possible range\n");
        return 0; // returns 0 if move is not in range
    }
}


int valid_move_left(int boardArr[ROWS][COLS])
{   // 1 if there is place and game can continue
    // 0 if there is no place left 
    for (int i=0; i<COLS; ++i)
    {
        if(boardArr[0][i] == 0)
        {
            return 1;
        }
    }
    printf("\nERROR: board is full game is over");
    return 0; 
}


int check_counter(int counter)
{
    switch(counter)
    {
        case 32:
            return 2; //winner is PL2
        case 4:
            return 1; //winner is PL1
        default:
            return 0; // no result 
    }
}


int check_winner(int boardArr[ROWS][COLS])
{
    int counter = 0;
    //horizontal
    int boardLine[COLS];

    for (int i=0; i<ROWS; i++)
    {
        for (int j= 0; j < COLS; j++)
        {
            boardLine[j] = boardArr[i][j];
        }
        for (int k = 0; k <= COLS - 4; k++)
        {
            counter = boardLine[k] + boardLine[k+1] + boardLine[k+2] + boardLine[k+3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2)
            {
                return check_counter(counter);
            }
        }
    } 

    //vertical
    for (int i=0; i<ROWS; i++)
    {
        for (int j= 0; j < COLS; j++)
        {
            boardLine[j] = boardArr[j][i];
        }
    
        for (int k = 0; k <= COLS - 4; k++)
        {
            counter = boardLine[k] + boardLine[k+1] + boardLine[k+2] + boardLine[k+3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2)
            {
                return check_counter(counter);
            }
        }
     
    }
    //positive - diagonal
    for (int i=0; i<ROWS; i++)
    {
        for (int j= ROWS; j < COLS; j++)
        {
            //boardLine[j] = boardArr[j][i];
        }


    }
    // if there is no winner 0, if PL1 is winner return 1, if PL2 is winner return 8
    return 0; 
}    
