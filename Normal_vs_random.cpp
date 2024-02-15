// Tic Tac Toe
#include <bits/stdc++.h>
using namespace std;
#define COMPUTER 1
#define RANDOM 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define RANDOMMOVE 'X'
int AI_win, Draw, Random_win;






void showBoard(char board[][SIDE])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}
void showInstructions()
{
    printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}
void initialise(char board[][SIDE])
{
    // Initially the board to '*' as said
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = '*';
    }
}
void declareWinner(int whoseTurn)
{
    if (whoseTurn == COMPUTER){
        printf("COMPUTER has won\n");
        AI_win++;
        }
    else{
        printf("RANDOM has won\n");
        Random_win++;
        }
}
bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return (true);
    }
    return (false);
}
bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*')
            return (true);
    }
    return (false);
}
bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*')
        return (true);
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*')
        return (true);
    return (false);
}
bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}





int minimax(char board[][SIDE], int depth, int alpha, int beta, bool isAI)
{
    int score = 0;
    if (gameOver(board))
    {
        if (isAI)
            return -10;
        else
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI)
            {
                int bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            score = minimax(board, depth + 1, alpha, beta, false);
                            board[i][j] = '*';
                            bestScore = max(bestScore, score);
                            alpha = max(alpha, bestScore);
                            if (beta <= alpha)
                                break; // Beta pruning
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                int bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = RANDOMMOVE;
                            score = minimax(board, depth + 1, alpha, beta, true);
                            board[i][j] = '*';
                            bestScore = min(bestScore, score);
                            beta = min(beta, bestScore);
                            if (beta <= alpha)
                                break; // Alpha pruning
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}










int bestMove(char board[][SIDE], int moveIndex)
{   int alpha = INT_MIN;
    int beta = INT_MAX;
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1,alpha,beta, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}
// A function to play Tic-Tac-Toe
void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;
    initialise(board);
    showInstructions();
    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        int n;
        if (whoseTurn == COMPUTER)
        {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in cell %d\n\n", COMPUTERMOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = RANDOM;
        }
        else if (whoseTurn == RANDOM)
        {      
            printf("You can insert in the following positions : ");
            for (int i = 0; i < SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
            printf("\n\nEnter the position = ");
            n = rand();
            n = n%9 +1;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = RANDOMMOVE;
                printf("\nRANDOM has put a %c in cell %d\n\n", RANDOMMOVE,
                       n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            }
            
        }
    }
    if (gameOver(board) == false && moveIndex == SIDE * SIDE){
        printf("It's a draw\n");
        Draw++;
        }
    else
    {
        if (whoseTurn == COMPUTER)
            whoseTurn = RANDOM;
        else if (whoseTurn == RANDOM)
            whoseTurn = COMPUTER;
        declareWinner(whoseTurn);
    }
}
int main()
{   srand(100);
    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    char cont = 'y';
    int trials = 10;
    int n = 0;
    while(n!= trials)
    {   n++;
        cout << endl << endl << "=================================INSTANCE#" << n <<"===================================="<< endl << endl ;
         int first_chance = rand()%2;
        if (first_chance)
            playTicTacToe(COMPUTER);
        else
            playTicTacToe(RANDOM);
    }


    printf("\n-------------------------------------------------------------------\n");
    cout << endl << endl << endl << "AFTER " << n << " TRIALS; " << endl;
    cout << "AI WINS: " << AI_win << endl;
    cout << "DRAWS: " << Draw << endl;
    cout << "RANDOM WINS: " << Random_win << endl;
    printf("\n-------------------------------------------------------------------\n");

    return (0);
}