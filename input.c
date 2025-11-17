#include "input.h"
#include "platform.h"
#include <stdio.h>

#ifdef _WIN32
    #include <conio.h>
#endif

#ifndef _WIN32
    #include <termios.h>
    #include <unistd.h>
    static struct termios oldTermios;
    static struct termios newTermios;
#endif

void initInput(void) {
#ifndef _WIN32
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldTermios);

    // Copy to new settings
    newTermios = oldTermios;

    // Disable canonical mode and echo for single key reading
    newTermios.c_lflag &= ~(ICANON | ECHO);

    // Set new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
#endif
}

void restoreInput(void) {
#ifndef _WIN32
    // Restore original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
#endif
}

