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

// Convert grid position to screen coordinates and draw box
void drawGridBox(int gridRow, int gridCol, int n, int startX, int startY, Color color) {
    int x = startX + gridCol * (BOX_WIDTH + 1);
    int y = startY + gridRow * (BOX_HEIGHT + 1);

    setColor(color);

    // Top border
    moveCursor(x, y);
    printf("+");
    for (int i = 0; i < BOX_WIDTH - 2; i++) printf("-");
    printf("+");

    // Middle rows
    for (int row = 1; row < BOX_HEIGHT - 1; row++) {
        moveCursor(x, y + row);
        printf("|");
        for (int i = 0; i < BOX_WIDTH - 2; i++) printf(" ");
        printf("|");
    }

    // Bottom border
    moveCursor(x, y + BOX_HEIGHT - 1);
    printf("+");
    for (int i = 0; i < BOX_WIDTH - 2; i++) printf("-");
    printf("+");

    resetColor();
    fflush(stdout);
}

// Draw number at grid position
void drawNumberAtPosition(int gridRow, int gridCol, int n, int num, int startX, int startY) {
    int x = startX + gridCol * (BOX_WIDTH + 1);
    int y = startY + gridRow * (BOX_HEIGHT + 1);

    char numStr[10];
    sprintf(numStr, "%d", num);

    int centerX = x + (BOX_WIDTH - strlen(numStr)) / 2;
    int centerY = y + BOX_HEIGHT / 2;

    drawText(centerX, centerY, numStr, YELLOW);
}

// Draw complete empty grid
void drawEmptyGrid(int n, int startX, int startY) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            drawGridBox(i, j, n, startX, startY, WHITE);
        }
    }
}

// Fill magic square with animation
void fillMagicSquareAnimated(int n, int startX, int startY) {
    for (int num = 1; num <= n * n; num++) {
        int row, col;
        calculatePosition(n, num, &row, &col);

        // Highlight box
        drawGridBox(row, col, n, startX, startY, CYAN);
        delaySeconds(1);

        // Draw number (this stays visible)
        drawNumberAtPosition(row, col, n, num, startX, startY);
        delaySeconds(1);

        // Redraw box border only (not the middle where number is)
        int x = startX + col * (BOX_WIDTH + 1);
        int y = startY + row * (BOX_HEIGHT + 1);

        setColor(WHITE);
        // Top border
        moveCursor(x, y);
        printf("+");
        for (int i = 0; i < BOX_WIDTH - 2; i++) printf("-");
        printf("+");

        // Left and right borders only
        for (int r = 1; r < BOX_HEIGHT - 1; r++) {
            moveCursor(x, y + r);
            printf("|");
            moveCursor(x + BOX_WIDTH - 1, y + r);
            printf("|");
        }

        // Bottom border
        moveCursor(x, y + BOX_HEIGHT - 1);
        printf("+");
        for (int i = 0; i < BOX_WIDTH - 2; i++) printf("-");
        printf("+");

        resetColor();
        fflush(stdout);
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
    int n;
    char buffer[100];

    clearScreen();
    drawText(5, 2, "=== Magic Square Generator ===", CYAN);
    drawText(5, 4, "Enter an odd number (3, 5, 7, or 9): ", GREEN);

    moveCursor(44, 4);
    setColor(WHITE);
    fflush(stdout);

    // Use fgets to read input properly
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        sscanf(buffer, "%d", &n);
    } else {
        n = 0;
    }

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
        drawText(5, 7, "Press Enter to exit...", YELLOW);
        fflush(stdout);
        getchar();
        return;
    }

    clearScreen();

    // Calculate centered position
    int totalWidth = n * (BOX_WIDTH + 1) + 1;
    int totalHeight = n * (BOX_HEIGHT + 1) + 1;
    int startX = (80 - totalWidth) / 2;
    int startY = (24 - totalHeight) / 2;

    // Display title
    char title[50];
    sprintf(title, "Magic Square %dx%d", n, n);
    drawText((80 - strlen(title)) / 2, 2, title, CYAN);

    // Draw and fill
    drawEmptyGrid(n, startX, startY);
    delaySeconds(1);
    fillMagicSquareAnimated(n, startX, startY);
    displayMagicSum(n, startY);

    // Wait for exit
    drawText(10, 23, "Press Enter to exit...", YELLOW);
    fflush(stdout);
    getchar();
    clearScreen();
}
