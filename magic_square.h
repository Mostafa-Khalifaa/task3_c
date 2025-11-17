#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include "color.h"

#define BOX_WIDTH 6
#define BOX_HEIGHT 3

// Initialize and run magic square program
void runMagicSquare(void);

// Get user input for square size
int getUserInput(void);

// Calculate position for a given number in magic square
void calculatePosition(int n, int num, int *row, int *col);

// Check if position is already occupied
int isOccupied(int n, int row, int col, int currentNum);

// Draw single box at grid position
void drawGridBox(int gridRow, int gridCol, int n, int startX, int startY, Color color);

// Draw number inside box at grid position
void drawNumberAtPosition(int gridRow, int gridCol, int n, int num, int startX, int startY);

// Draw complete empty grid
void drawEmptyGrid(int n, int startX, int startY);

// Fill magic square with numbers (animated)
void fillMagicSquareAnimated(int n, int startX, int startY);

// Display magic sum
void displayMagicSum(int n, int startY);

#endif // MAGIC_SQUARE_H
