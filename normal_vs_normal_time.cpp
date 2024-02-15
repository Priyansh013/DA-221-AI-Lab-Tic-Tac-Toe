// Tic Tac Toe
#include <bits/stdc++.h>
#include <chrono> 
using namespace std;
#define P1 1
#define P2 2
#define SIDE 3
#define P1MOVE 'O'
#define P2MOVE 'X'


int p1_wins=0, draw=0, p2_wins=0;






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
    if (whoseTurn == P1)
        {printf("P1 has won\n"); p1_wins++;}
    else
       { printf("P2 has won\n");p2_wins++;}
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




int minimaxp1(char board[][SIDE], int depth, bool isAI)
{
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
                            board[i][j] = P1MOVE;
                            score = minimaxp1(board, depth + 1, false);
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
                            board[i][j] = P2MOVE;
                            score = minimaxp1(board, depth + 1, true);
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

int minimaxp2(char board[][SIDE], int depth, bool isAI)
{
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
                            board[i][j] = P2MOVE;
                            score = minimaxp2(board, depth + 1, false);
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
                            board[i][j] = P1MOVE;
                            score = minimaxp2(board, depth + 1, true);
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



int bestMovep1(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = P1MOVE;
                score = minimaxp1(board, moveIndex + 1, false);
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


int bestMovep2(char board[][SIDE], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = P2MOVE;
                score = minimaxp2(board, moveIndex + 1, false);
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
        if (whoseTurn == P1)
        {   
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = P1MOVE;
            printf("P1 has put a %c in cell %d\n\n", P1MOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = P2;
        }
        else if (whoseTurn == P2)
        {
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = P2MOVE;
            printf("P2 has put a %c in cell %d\n\n", P2MOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = P1;
        }


    while (gameOver(board) == false && moveIndex != SIDE * SIDE)
    {
        if (whoseTurn == P1)
        {
            n = bestMovep1(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = P1MOVE;
            printf("P1 has put a %c in cell %d\n\n", P1MOVE,
                   n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = P2;
        }
        else if (whoseTurn == P2)
        {
             n = bestMovep2(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = P2MOVE;
            printf("P2 has put a %c in cell %d\n\n", P2MOVE,
                   n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = P1;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
            cout << endl << "Position is occupied, select any one place from the available places" << endl << endl;
           }
            else if (n < 0 || n > 8)
            {
                printf("Invalid position\n");
            }
        }
    
    if (gameOver(board) == false && moveIndex == SIDE * SIDE)
        {printf("It's a draw\n"); draw++;}
    else
    {
        if (whoseTurn == P1)
            whoseTurn = P2;
        else if (whoseTurn == P2)
            whoseTurn = P1;
        declareWinner(whoseTurn);
    }
}
int main()
{

   auto start = std::chrono::high_resolution_clock::now();


    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    

    srand(110);
    int trials = 100;
    int n = trials;
    

    while (trials--)
    {
        int first_chance = rand() % 2;
        if (first_chance)
            playTicTacToe(P1);
        else
            playTicTacToe(P2);
    }
    

    printf("\n-------------------------------------------------------------------\n");
    cout << endl<< endl << endl << "AFTER " << n << " TRIALS; " << endl;
    cout << "P1 WINS: " << p1_wins << endl;
    cout << "DRAWS: " << draw << endl;
    cout << "P2 WINS: " << p2_wins << endl;
    printf("\n-------------------------------------------------------------------\n\n");


    
    auto stop = std::chrono::high_resolution_clock::now();
    // Calculate the duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Output the duration
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    printf("\n-------------------------------------------------------------------\n");


    


    return (0);
}