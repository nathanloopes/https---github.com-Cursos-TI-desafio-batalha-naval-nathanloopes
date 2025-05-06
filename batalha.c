#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define SHIP_SIZE 3

void printBoard(int board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == 0)
                printf("~ "); // Água
            else if (board[i][j] == 3)
                printf("S "); // Navio
            else if (board[i][j] == 5)
                printf("X "); // Área afetada pela habilidade
        }
        printf("\n");
    }
}

void placeShipHorizontal(int board[SIZE][SIZE], int row, int col)
{
    for (int i = 0; i < SHIP_SIZE; i++)
    {
        board[row][col + i] = 3;
    }
}

void placeShipVertical(int board[SIZE][SIZE], int row, int col)
{
    for (int i = 0; i < SHIP_SIZE; i++)
    {
        board[row + i][col] = 3;
    }
}

void placeShipDiagonal(int board[SIZE][SIZE], int row, int col, int direction)
{
    for (int i = 0; i < SHIP_SIZE; i++)
    {
        if (direction == 1)
        {
            board[row + i][col + i] = 3;
        }
        else
        {
            board[row + i][col - i] = 3;
        }
    }
}

void applyCone(int board[SIZE][SIZE], int row, int col)
{
    int size = 3;
    for (int i = 0; i < size; i++)
    {
        for (int j = col - i; j <= col + i; j++)
        {
            if (i + row < SIZE && j >= 0 && j < SIZE)
                board[i + row][j] = 5; // Área afetada pelo cone
        }
    }
}

void applyCross(int board[SIZE][SIZE], int row, int col)
{
    int size = 1;
    for (int i = -size; i <= size; i++)
    {
        if (row + i >= 0 && row + i < SIZE)
            board[row + i][col] = 5; // Área afetada pela cruz
        if (col + i >= 0 && col + i < SIZE)
            board[row][col + i] = 5; // Área afetada pela cruz
    }
}

void applyOctahedron(int board[SIZE][SIZE], int row, int col)
{
    int size = 3;
    for (int i = -size; i <= size; i++)
    {
        for (int j = -size + abs(i); j <= size - abs(i); j++)
        {
            if (row + i >= 0 && row + i < SIZE && col + j >= 0 && col + j < SIZE)
                board[row + i][col + j] = 5; // Área afetada pelo octaedro
        }
    }
}

int main()
{
    int board[SIZE][SIZE] = {0};

    placeShipHorizontal(board, 1, 2);
    placeShipVertical(board, 5, 5);
    placeShipDiagonal(board, 3, 3, 1);
    placeShipDiagonal(board, 6, 6, 2);

    applyCone(board, 4, 4);
    applyCross(board, 5, 5);
    applyOctahedron(board, 6, 6);

    printf("Tabuleiro Final:\n");
    printBoard(board);

    return 0;
}
