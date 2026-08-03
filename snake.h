#ifndef SNAKE_H
#define SNAKE_H

#define WIDTH  20
#define HEIGHT 20
#define MAX_LEN 100

// 0=Up, 1=Down, 2=Left, 3=Right
extern int snake_x[MAX_LEN];
extern int snake_y[MAX_LEN];
extern int snake_len;
extern int food_x;
extern int food_y;
extern int direction;
extern int score;
extern int game_over;
extern int pause;

void setup(void);
void draw(void);
void input(void);
void logic(void);

#endif
