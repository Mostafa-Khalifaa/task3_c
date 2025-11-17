#include "draw.h"
#include "cursor.h"
#include "color.h"
#include "screen.h"
#include <stdio.h>

void drawText(int x, int y, const char *text, Color color) {
    moveCursor(x, y);
    setColor(color);
    printf("%s", text);
    resetColor();
    //تضمن إن كل النص اللي كتبناه يظهر فورًا على الشاشة.
    fflush(stdout);
}

void showInitial(int x, int y, const char *text, Color color) {
    drawText(x, y, text, color);
}

void showStatementScreen() {
    clearScreen();
    drawText(5, 2, "=== Statement Screen ===", CYAN);
    drawText(5, 4, "Operation completed successfully!", GREEN);
    drawText(5, 6, "Press Enter to continue...", YELLOW);
}
