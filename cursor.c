#include "cursor.h"
#include "platform.h"
#include <stdio.h>

void moveCursor(int x, int y) {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    // Create a COORD struct to store cursor position.
    COORD pos = { (SHORT)(x - 1), (SHORT)(y - 1) };
    SetConsoleCursorPosition(h, pos);
#else
 // Moves cursor to (y, x) because ANSI uses row first.
    printf("\033[%d;%dH", y, x);
#endif
}
