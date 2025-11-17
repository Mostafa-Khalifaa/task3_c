#include "color.h"
#include "platform.h"
#include <stdio.h>

void setColor(Color color) {
#ifdef _WIN32
    // Get the console output handle (where text is printed)
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = 0;

    // Map our custom color values to Windows console color flags
    switch (color) {
        case BLACK:   attr = 0; break;
        case RED:     attr = FOREGROUND_RED; break;
        case GREEN:   attr = FOREGROUND_GREEN; break;
        case YELLOW:  attr = FOREGROUND_RED | FOREGROUND_GREEN; break;
        case BLUE:    attr = FOREGROUND_BLUE; break;
        case MAGENTA: attr = FOREGROUND_RED | FOREGROUND_BLUE; break;
        case CYAN:    attr = FOREGROUND_GREEN | FOREGROUND_BLUE; break;
        default:      attr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
    }

    attr |= FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(h, attr);
#else
    // Linux terminal uses ANSI codes: 30–37 for text colors
    int code = 30 + color;
    printf("\033[%dm", code);
#endif
}

void resetColor(void) {
#ifdef _WIN32
// Reset text to normal white color in Windows
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    printf("\033[0m");
#endif
}
