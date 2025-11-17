#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

typedef enum {
    BLACK, RED, GREEN, YELLOW,
    BLUE, MAGENTA, CYAN, WHITE
} Color;

void setColor(Color color);
void resetColor(void);

#endif // COLOR_H_INCLUDED
