// I will test some functions here
// import everything from main.c

#include "main.c" 

int main(){
    //initiate the game
    GameBoard *game_board = initializeGameBoard(NUM_OF_CARDS, NUM_OF_FOUNDATIONS, NUM_OF_COLUMNS);
    //print the deck with printCardNode func
    printCardNode(game_board->deck);

    // print the waste with printCardNode func
    printCardNode(game_board->waste);

    // move 5 card from deck to waste

    printf("move 5 card from deck to waste\n");

    for (int i = 0; i < 5; i++)
    {
        Card *card = removeCard(game_board->deck, 0, false);
        insertCard(game_board->waste, *card, 0, false);
        free(card);
    }

    // print the waste with printCardNode func again to compare
    printCardNode(game_board->waste);


}