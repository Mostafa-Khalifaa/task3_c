#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "input.h"
#include "magic_square.h"

int main() {
    initInput();
    runMagicSquare();
    restoreInput();
    return 0;
}
