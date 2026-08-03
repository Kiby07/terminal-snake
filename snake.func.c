#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> //包含kbhit、getch函数读取方向
#include <windows.h>
#include <time.h> //将时刻转变为随机数

int snake_x[MAX_LEN];
int snake_y[MAX_LEN];
int snake_len = 3;
int food_x, food_y;
int direction = 2;
int score = 0;
int game_over = 0;
int pause=1;

void setup() {
    int i;
    for (i = 0; i < snake_len; i++) {
        snake_x[i] = WIDTH / 2;  //初始化蛇头位置
        snake_y[i] = HEIGHT / 2 + i;
    }
    srand((unsigned)time(NULL));
    food_x = rand() % (WIDTH - 2) + 1; //控制food在游戏框内
    food_y = rand() % (HEIGHT - 2) + 1;
}

void draw() {
    int x, y, i;
    system("cls");  //清屏画面便于根据键盘操作更新画面
    printf("=== SNAKE ===\n");
    printf("WASD/Arrows to move, Q to quit\n");
    if(pause)
        printf("Press space to start\n");
    else
        printf("Press space to pause\n");
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                printf("#");
            } else if (x == food_x && y == food_y) {
                printf("*");
            } else {
                int is_body = 0;
                for (i = 0; i < snake_len; i++) {
                    if (snake_x[i] == x && snake_y[i] == y) {
                        printf(i == 0 ? "O" : "o"); //画出蛇
                        is_body = 1;
                        break;
                    }
                }
                if (!is_body) printf(" ");
            }
        }
        printf("\n");
    }
}

void input() {  //判断键盘输入的方向
    if (_kbhit()) {
        char key = _getch();
        if (key == -32 || key == 0) {
            key = _getch();
            if (key == 72 && direction != 1) direction = 0; //向上
            if (key == 80 && direction != 0) direction = 1; //向下
            if (key == 75 && direction != 3) direction = 2; //向左
            if (key == 77 && direction != 2) direction = 3; //向右
        } else {
            if(key==' ')
            {
                pause=!pause;
                return;
            }
            if ((key == 'w' || key == 'W') && direction != 1) direction = 0;
            if ((key == 's' || key == 'S') && direction != 0) direction = 1;
            if ((key == 'a' || key == 'A') && direction != 3) direction = 2;
            if ((key == 'd' || key == 'D') && direction != 2) direction = 3;
            if (key == 'q' || key == 'Q') game_over = 1;
        }
    }
}

void logic() {  //更新蛇的位置
    int i;
    for (i = snake_len - 1; i > 0; i--) {
        snake_x[i] = snake_x[i - 1];
        snake_y[i] = snake_y[i - 1];
    }

    if (direction == 0) snake_y[0]--;
    if (direction == 1) snake_y[0]++;
    if (direction == 2) snake_x[0]--;
    if (direction == 3) snake_x[0]++;

    if (snake_x[0] <= 0 || snake_x[0] >= WIDTH - 1 ||
        snake_y[0] <= 0 || snake_y[0] >= HEIGHT - 1) { //判断是否撞墙
        game_over = 1;
    }

    for (i = 1; i < snake_len; i++) {
        if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) { //撞到蛇身也视为失败
            game_over = 1;
        }
    }

    if (snake_x[0] == food_x && snake_y[0] == food_y) {
        score += 10;  //加分制度
        snake_len++;
        food_x = rand() % (WIDTH - 2) + 1;  //根据时间随机更新food位置
        food_y = rand() % (HEIGHT - 2) + 1;
    }
}
