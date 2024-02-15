// Tic Tac Toe
#include <bits/stdc++.h>
using namespace std;
#define PRUNE 1
#define NORMAL 2
#define SIDE 3
#define PRUNEMOVE 'O'
#define NORMALMOVE 'X'

long long prune_count = 0;
long long normal_count = 0;
int prune_win, Draw, normal_win;

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
    if (whoseTurn == PRUNE)
    {
        printf("PRUNE has won\n");
        prune_win++;
    }
    else
    {
        printf("NORMAL has won\n");
        normal_win++;
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

int minimax_prune(char board[][SIDE], int depth, int alpha, int beta, bool isAI)
{
    prune_count++;
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
                            board[i][j] = PRUNEMOVE;
                            score = minimax_prune(board, depth + 1, alpha, beta, false);
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
                            board[i][j] = NORMALMOVE;
                            score = minimax_prune(board, depth + 1, alpha, beta, true);
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

int bestMoveprune(char board[][SIDE], int moveIndex)
{
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = PRUNEMOVE;
                score = minimax_prune(board, moveIndex + 1, alpha, beta, false);
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

int minimax(char board[][SIDE], int depth, bool isAI)
{
    normal_count++;
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = NORMALMOVE;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = PRUNEMOVE;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
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
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = NORMALMOVE;
                score = minimax(board, moveIndex + 1, false);
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
    
        int n = rand()%9 + 1;
        n--;
        if (whoseTurn == PRUNE)
        {   
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = PRUNEMOVE;
            printf("PRUNE has put a %c in cell %d\n\n", PRUNEMOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = NORMAL;
        }
        else if (whoseTurn == NORMAL)
        {
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = NORMALMOVE;
            printf("NORMAL has put a %c in cell %d\n\n", NORMALMOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = PRUNE;
        }
    


        while (gameOver(board) == false && moveIndex != SIDE * SIDE)
        {
            if (whoseTurn == PRUNE)
            {
                n = bestMoveprune(board, moveIndex);
                x = n / SIDE;
                y = n % SIDE;
                board[x][y] = PRUNEMOVE;
                printf("PRUNE has put a %c in cell %d\n\n", PRUNEMOVE,
                       n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = NORMAL;
            }
            else if (whoseTurn == NORMAL)
            {
                n = bestMove(board, moveIndex);
                x = n / SIDE;
                y = n % SIDE;
                board[x][y] = NORMALMOVE;
                printf("NORMAL has put a %c in cell %d\n\n", NORMALMOVE,
                       n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = PRUNE;
            }
        }

        if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        {
            printf("It's a draw\n");
            Draw++;
        }
        else
        {
            if (whoseTurn == PRUNE)
                whoseTurn = NORMAL;
            else if (whoseTurn == NORMAL)
                whoseTurn = PRUNE;
            declareWinner(whoseTurn);
        }
    
}



int main()
{
    srand(101);
    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    char cont = 'y';
    int trials = 100;
    int n = trials;
    while (trials--)
    {
        int first_chance = rand() % 2;
        if (first_chance)
            playTicTacToe(PRUNE);
        else
            playTicTacToe(NORMAL);
    }

    cout << "\n-------------------------------------------------------------------\n";
    cout << endl<< endl << endl << "AFTER " << n << " TRIALS; " << endl;
    cout << "PRUNE WINS: " << prune_win << endl;
    cout << "DRAWS: " << Draw << endl;
    cout << "NORMAL WINS: " << normal_win << endl;
    cout << "\n-------------------------------------------------------------------" << endl;
    cout << endl << "Number of nodes visited in MINIMAX with PRUNING: " << prune_count << endl;
    cout << endl  << "Number of nodes visited in MINIMAX without PRUNING: " << normal_count << endl;
    printf("\n-------------------------------------------------------------------\n");

    return (0);
}