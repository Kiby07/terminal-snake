#include "snake.h"
#include <stdio.h>
#include <windows.h>

int main() {
    setup();
    while (!game_over) {
        draw();
        input();
        if(!pause)
          logic();
        Sleep(100);
    }
    printf("\nGame Over! Final Score: %d\n", score);
    return 0;
}
