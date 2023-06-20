#include <stdio.h>
#include <stdlib.h>

#define ROWS 6
#define COLS 7
#define PL1 1
#define PL2 8


void print_board(int boardArr[ROWS][COLS]);                      // prints the board with tabs and other stuff to terminal  
int make_move(int boardArr[ROWS][COLS], int player, int col);    //returns 0 if error, returns 1 if succesful 
int check_input_range(int boardArr[ROWS][COLS], int col);        // to check the if the input is in range of game board
int check_col(int boardArr[ROWS][COLS], int col);                //check if the column is empty
int valid_move_left(int boardArr[ROWS][COLS]);                   // if valid move left returns 1, otherwise 0
int check_counter(int counter);                                  // returns 1 if pl1 wins, returns 2 if pl2 wins, if there isn't any winning situation returns 0
int check_winner(int boardArr[ROWS][COLS]);                      // calculates and creates counter variable gives it to check_counter function


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
                printf("player 1 won");
                break;
            case 2:
                printf("player 2 won");
                break;
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
    //returns 0 if error, returns 1 if succesful
    
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
    int boardLine[COLS] = {};

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
    for (int i=0; i<COLS; i++)
    {
        for (int j= 0; j < ROWS; j++)
        {
            boardLine[j] = boardArr[j][i];
        }
    
        for (int k = 0; k <= ROWS - 4; k++)
        {
            counter = boardLine[k] + boardLine[k+1] + boardLine[k+2] + boardLine[k+3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2)
            {
                return check_counter(counter);
            }
        }
    }
    
    //positive diagonal 
    int boardDiagolLine[4] = {};
    for (int i = 3; i <= ROWS - 1; i++)
    {
        for (int j = 0; j < ROWS - 4; j++)
        {
            boardDiagolLine[0] = boardArr[i  ][j  ];
            boardDiagolLine[1] = boardArr[i-1][j+1];
            boardDiagolLine[2] = boardArr[i-2][j+2];
            boardDiagolLine[3] = boardArr[i-3][j+3];
            
            counter = boardDiagolLine[0] + boardDiagolLine[1] + boardDiagolLine[2] + boardDiagolLine[3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2)
            {
                return check_counter(counter);
            }

        }            
    }
    
    //negative diagonal 
    boardDiagolLine[0] = 0;
    boardDiagolLine[1] = 0;
    boardDiagolLine[2] = 0;
    boardDiagolLine[3] = 0;

    for (int i = 3; i <= ROWS - 1; i++)
    {
        for (int j = COLS - 1; j >= 3; j--)
        {
            boardDiagolLine[0] = boardArr[i  ][j  ];
            boardDiagolLine[1] = boardArr[i-1][j-1];
            boardDiagolLine[2] = boardArr[i-2][j-2];
            boardDiagolLine[3] = boardArr[i-3][j-3];
            
            counter = boardDiagolLine[0] + boardDiagolLine[1] + boardDiagolLine[2] + boardDiagolLine[3];
            if (check_counter(counter) == 1 || check_counter(counter) == 2)
            {
                return check_counter(counter);
            }
        }            
    }
}
