// this file will run the solitaire game on terminal

//includes here
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


// constanst that will be used in the program
#define NUM_OF_CARDS 52
#define NUM_OF_SUITS 4
#define NUM_OF_VALUES 13

#define MAX_SIZE_CN 100
#define MAX_SIZE_NAME 15


#define NUM_OF_COLUMNS 7
#define NUM_OF_FOUNDATIONS 4


//struct that will represent the card
typedef struct Card
{
    char suit; // 'H' for hearts, 'D' for diamonds, 'S' for spades, 'C' for clubs
    int value;
    bool faceUp;

} Card;


typedef struct CardNode
{
    Card card;
    struct CardNode *next;

} CardNode;


typedef struct GameBoard
{
    CardNode *deck;
    CardNode *waste;
    CardNode *foundations[NUM_OF_FOUNDATIONS];
    CardNode *columns[NUM_OF_COLUMNS];

} GameBoard;


/*
functions to create
-- createCardNode: create cardnode with number of cards given as parameter
-- initializeRandomDeck: initialize the deck with randomly ordered cards
-- initializeWaste: initialize the waste with no cards
-- initializeFoundations: initialize the certain amount of foundations with no cards
-- initializeColumns: initialize the columns with cards in order
-- initializeGameBoard: initialize the gameboard with all the above functions

*/

//function prototypes -- functions to create the game
CardNode *createCardNode(int numOfCards);
CardNode *initializeRandomDeck(int numOfCards);
CardNode *initializeWaste();
CardNode **initializeFoundations(int numOfFoundations);
CardNode **initializeColumns(int numOfColumns);
GameBoard *initializeGameBoard(int numOfCards, int numOfFoundations, int numOfColumns);


// primitive functions -- for moveCard function
Card *removeCard(CardNode *head, int index, bool last_element); //if last_element is true, then index is ignored, remove from the end
void insertCard(CardNode *head, Card card, int index, bool last_element); //if last_element is true, then index is ignored, insert at the end

//function prototypes -- functions to play the game
void dealCardsToStartingPosition(GameBoard *gameBoard);

//function prototypes -- functions to print the game
void printCard(Card card);
void printCardNode(CardNode *head);
void printGameBoard(GameBoard *gameBoard);


int main()
{
    // initialize the gameboard
    GameBoard *gameBoard = initializeGameBoard(
                               NUM_OF_CARDS, 
                               NUM_OF_FOUNDATIONS, 
                               NUM_OF_COLUMNS
                               );

    // remove the first card from deck and insert it to waste
    Card *card = removeCard(gameBoard->deck, 0, false);
    insertCard(gameBoard->waste, *card, 0, true);
    free(card);
    
    // print the gameboard
    printGameBoard(gameBoard);

    // free the memory
    free(gameBoard);

    return 0;
}





//function definitions -- functions to create the game
CardNode *createCardNode(int numOfCards)
{
    CardNode *head = NULL;
    CardNode *temp = NULL;
    CardNode *p = NULL;

    for (int i = 0; i < numOfCards; i++)
    {
    
        temp = (CardNode *)malloc(sizeof(CardNode));
        temp->card.suit = ' ';
        temp->card.value = 0;
        temp->card.faceUp = false;
        temp->next = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            p = head;
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }

    return head;
}

CardNode *initializeRandomDeck(int numOfCards)
{
    CardNode *head = createCardNode(numOfCards);
    CardNode *p = head;

    char suits[NUM_OF_SUITS] = {'H', 'D', 'S', 'C'}; 
    int values[NUM_OF_VALUES] = {1,2,3,4,5,6,7,8,9,10,11,12,13};

    for (int i = 0; i < NUM_OF_SUITS; i++)
    {
        for (int j = 0; j < NUM_OF_VALUES; j++) 
        {
            p->card.suit = suits[i];
            p->card.value = values[j];
            p->card.faceUp = false;
            p = p->next;
        }
    }

    // randomly order the cards while providing random seed for rand()
    srand(time(NULL));
    for (int i = 0; i < numOfCards; i++)
    {
        int random = rand() % numOfCards;
        CardNode *temp = head;
        for (int j = 0; j < random; j++)
        {
            temp = temp->next;
        }
        CardNode *temp2 = head;
        for (int j = 0; j < i; j++)
        {
            temp2 = temp2->next;
        }
        CardNode *temp3 = (CardNode *)malloc(sizeof(CardNode));
        temp3->card.suit = temp->card.suit;
        temp3->card.value = temp->card.value;
        temp3->card.faceUp = temp->card.faceUp;
        temp->card.suit = temp2->card.suit;
        temp->card.value = temp2->card.value;
        temp->card.faceUp = temp2->card.faceUp;
        temp2->card.suit = temp3->card.suit;
        temp2->card.value = temp3->card.value;
        temp2->card.faceUp = temp3->card.faceUp;
        free(temp3);
    }

    return head;
}

CardNode *initializeWaste()
{
    CardNode *head = createCardNode(1);
    return head;
}

CardNode **initializeFoundations(int numOfFoundations)
{
    CardNode** CardNodePArray = (CardNode **)malloc(sizeof(CardNode*) * numOfFoundations);
    
    for (int i = 0; i < numOfFoundations; i++)
    {
        CardNodePArray[i] = createCardNode(1);
    }

    return CardNodePArray;
}

CardNode **initializeColumns(int numOfColumns)
{
    // init the array of cardnode pointers
    CardNode** CardNodePArray = (CardNode **)malloc(sizeof(CardNode*) * numOfColumns);

    // init each cardnode in the array
    for (int i = 0; i < numOfColumns; i++)
    {
        CardNodePArray[i] = createCardNode(1);
    }

    return CardNodePArray;
}

GameBoard *initializeGameBoard(
    int numOfCards, 
    int numOfFoundations, 
    int numOfColumns)


{
    GameBoard *gameBoard = (GameBoard *)malloc(sizeof(GameBoard));
    gameBoard->deck = initializeRandomDeck(numOfCards);
    gameBoard->waste = initializeWaste();
    
    CardNode **foundations = initializeFoundations(numOfFoundations);
    for (int i = 0; i < numOfFoundations; i++){
        gameBoard->foundations[i] = foundations[i];
    }
    
    CardNode **columns = initializeColumns(numOfColumns);
    for (int i = 0; i < numOfColumns; i++){
        gameBoard->columns[i] = columns[i];
    }

    return gameBoard;
}


// primitive functions -- for moveCard function
Card *removeCard(CardNode *head, int index, bool last_element)
{
    CardNode *previous = NULL;
    CardNode *p = head;
    Card *card = (Card *)malloc(sizeof(Card));

    if (last_element)
    {
        while (p->next->next != NULL)
        {
            p = p->next;
        }
        card->suit = p->card.suit;
        card->value = p->card.value;
        card->faceUp = p->card.faceUp;
        free(p);
        p = NULL;
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            previous = p;
            p = p->next;
        }

        CardNode *temp = p;
        card->suit = temp->card.suit;
        card->value = temp->card.value;
        card->faceUp = temp->card.faceUp;
        if (previous != NULL) {previous->next = temp->next;}
        else {head = temp->next;}
        free(temp);
        temp = NULL;
    }

    return card;
}

void insertCard(CardNode *head, Card card, int index, bool last_element)
{

    // create temp variable with createCardNode function
    CardNode *temp = createCardNode(1);
    temp->card.suit = card.suit;
    temp->card.value = card.value;
    temp->card.faceUp = card.faceUp;

    CardNode *p = head;

    if (last_element)
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
        temp->next = NULL;
    }
    else
    {
        for (int i = 0; i < index - 1; i++)
        {
            p = p->next;
        }
        temp->next = p->next;
        p->next = temp;
    }
}


// void dealCardsToStartingPosition(GameBoard *gameBoard)
// {
//     // deal cards to the columns
//     for (int i = 0; i < NUM_OF_COLUMNS; i++)
//     {
//         Card *card = removeCard(gameBoard->deck, 0, false);
//         insertCard(*(gameBoard->columns[i]), *card, 0, true);
//         free(card);    
//     }

//     // flip the last card in each column
//     for (int i = 0; i < NUM_OF_COLUMNS; i++)
//     {
//         CardNode *p = gameBoard->columns[i];
//         for (int j = 0; j < i; j++)
//         {
//             p = p->next;
//         }
//         p->card.faceUp = true;
//     }
// }

void printCard(Card card)
{
    if (card.faceUp)
    {
        // in total the printed card should take up 3 char wide
        printf("%c%02d", card.suit, card.value);
    }
    else
    {
        printf("XXX");
    }
}

void printCardNode(CardNode *head)
{
    CardNode *p = head;
    while (p != NULL)
    {
        printCard(p->card);
        printf(" ");
        p = p->next;
    }
    printf("\n");
}

void printGameBoard(GameBoard *gameBoard)
{
    printf("Deck: ");
    printCardNode(gameBoard->deck);
    printf("Waste: ");
    printCardNode(gameBoard->waste);
    printf("Foundations: \n");
    for (int i = 0; i < NUM_OF_FOUNDATIONS; i++)
    {
        printCardNode(gameBoard->foundations[i]);
        printf(" ");
        printf("\n");
    }
    
    printf("Columns: \n");
    for (int i = 0; i < NUM_OF_COLUMNS; i++)
    {
        printCardNode(gameBoard->columns[i]);
        printf(" ");
        printf("\n");
    }
    
    printf("\n");
}
