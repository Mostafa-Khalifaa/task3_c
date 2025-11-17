#ifndef INPUT_H
#define INPUT_H

// Initialize input system (for Linux terminal settings)
void initInput(void);

// Restore input settings (for Linux)
void restoreInput(void);

// Wait for any key press
void waitForKey(void);

#endif // INPUT_H
