#include "magic_square.h"
#include "screen.h"
#include "draw.h"
#include "cursor.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// Calculate where number should be placed using De La Loubere algorithm
void calculatePosition(int n, int num, int *row, int *col) {
    *row = 0;
    *col = n / 2;

    for (int i = 1; i < num; i++) {
        int newRow = (*row - 1 + n) % n;
        int newCol = (*col + 1) % n;

        if (isOccupied(n, newRow, newCol, i)) {
            *row = (*row + 1) % n;
        } else {
            *row = newRow;
            *col = newCol;
        }
    }
}

// Check if a grid position is already filled
int isOccupied(int n, int targetRow, int targetCol, int upToNum) {
    for (int num = 1; num < upToNum; num++) {
        int r, c;
        calculatePosition(n, num, &r, &c);
        if (r == targetRow && c == targetCol) {
            return 1;
        }
    }
    return 0;
}


// Draw number at grid position
void drawNumberAtPosition(int gridRow, int gridCol, int n, int num, int startX, int startY) {
    int x = startX + gridCol * BOX_WIDTH;
    int y = startY + gridRow * BOX_HEIGHT;

    char numStr[10];
    sprintf(numStr, "%d", num);

    int centerX = x + (BOX_WIDTH - strlen(numStr)) / 2;
    int centerY = y + BOX_HEIGHT / 2;

    drawText(centerX, centerY, numStr, YELLOW);
}


// Fill magic square with animation (numbers only)
void fillMagicSquareAnimated(int n, int startX, int startY) {
    for (int num = 1; num <= n * n; num++) {
        int row, col;
        calculatePosition(n, num, &row, &col);

        // Draw the number directly
        drawNumberAtPosition(row, col, n, num, startX, startY);

        delaySeconds(1);
    }
}

// Display the magic sum formula result
void displayMagicSum(int n, int startY) {
    int totalHeight = n * (BOX_HEIGHT + 1) + 1;
    int magicSum = n * (n * n + 1) / 2;

    char sumText[50];
    sprintf(sumText, "Magic Sum: %d", magicSum);
    drawText((80 - strlen(sumText)) / 2, startY + totalHeight + 1, sumText, GREEN);
}

// Get valid odd number from user
int getUserInput(void) {
    int n = 0;

    clearScreen();
    drawText(5, 2, "=== Magic Square Generator ===", CYAN);
    drawText(5, 4, "Enter an odd number (3, 5, 7, or 9): ", GREEN);

    moveCursor(44, 4);
    setColor(WHITE);
    fflush(stdout);

    // Temporarily restore terminal for normal input
#ifndef _WIN32
    struct termios old, new;
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
#endif

    scanf("%d", &n);

    // Clear input buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

#ifndef _WIN32
    // Restore non-canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
#endif

    resetColor();
    return n;
}

// Main function to run the magic square program
void runMagicSquare(void) {
    int n = getUserInput();

    // Validate input
    if (n < 3 || n > 9 || n % 2 == 0) {
        clearScreen();
        drawText(5, 5, "Invalid! Enter an odd number between 3 and 9.", RED);
        drawText(5, 7, "Press any key to exit...", YELLOW);
        fflush(stdout);

        // Wait for any key
        waitForKey();
        return;
    }

    clearScreen();

    // Calculate centered position (smaller spacing without boxes)
    int totalWidth = n * BOX_WIDTH;
    int totalHeight = n * BOX_HEIGHT;
    int startX = (80 - totalWidth) / 2;
    int startY = (24 - totalHeight) / 2;

    // Display title
    char title[50];
    sprintf(title, "Magic Square %dx%d", n, n);
    drawText((80 - strlen(title)) / 2, 2, title, CYAN);

    // Fill magic square with numbers only
    fillMagicSquareAnimated(n, startX, startY);
    displayMagicSum(n, startY);

    // Wait for exit
    drawText(10, 23, "Press any key to exit...", YELLOW);
    fflush(stdout);
    waitForKey();
    clearScreen();
}
