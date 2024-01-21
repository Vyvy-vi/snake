#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

void DrawSnake(void);
void UpdatePosition(void);

#define SCREEN_SIZE 600
#define CELL_SIZE 30
#define FOOD_SIZE 20
#define HEAD_COLOR \
    CLITERAL(Color) { 253, 249, 0, 255 }
#define TAIL_COLOR \
    CLITERAL(Color) { 243, 255, 107, 255 }

const int FOOD_SPACING = ((CELL_SIZE - FOOD_SIZE) / 2);
const int START_POINT = SCREEN_SIZE / 2;
int score = 0;

typedef struct node
{
    int x;
    int y;
} node;

node Snake[(SCREEN_SIZE * SCREEN_SIZE) / (CELL_SIZE * CELL_SIZE)];
int snake_size = 1;
bool food_present = false;
node Food;

node offset = {0, 0};

int main(void)
{
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Snake");
    Snake[0].x = START_POINT;
    Snake[0].y = START_POINT;
    SetTargetFPS(8);

    while (!WindowShouldClose())
    {
        DrawSnake();
        UpdatePosition();
    }

    CloseWindow();

    return 0;
}

void UpdatePosition()
{
    if (!food_present)
    {
        Food.x = rand() % (SCREEN_SIZE / CELL_SIZE) * CELL_SIZE + FOOD_SPACING;
        Food.y = rand() % (SCREEN_SIZE / CELL_SIZE) * CELL_SIZE + FOOD_SPACING;
        food_present = true;
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        offset.x = CELL_SIZE;
        offset.y = 0;
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        offset.x = -CELL_SIZE;
        offset.y = 0;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        offset.x = 0;
        offset.y = -CELL_SIZE;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        if (Snake[0].y == SCREEN_SIZE - CELL_SIZE)
            CloseWindow();
        offset.x = 0;
        offset.y = CELL_SIZE;
    }

    for (int i = snake_size - 1; i > 0; i--)
    {
        Snake[i] = Snake[i - 1];

        if (food_present && Food.x - FOOD_SPACING == Snake[i].x && Food.y - FOOD_SPACING == Snake[i].y)
            food_present = false;
    }

    Snake[0].x += offset.x;
    Snake[0].y += offset.y;

    if (food_present && Snake[0].x == Food.x - FOOD_SPACING && Snake[0].y == Food.y - FOOD_SPACING)
    {
        food_present = false;
        Snake[snake_size] = Snake[snake_size - 1];
        snake_size++;
        score += 10;
    }

    if (Snake[0].x < 0 || Snake[0].x > SCREEN_SIZE - CELL_SIZE || Snake[0].y < 0 || Snake[0].y > SCREEN_SIZE - CELL_SIZE)
    {
        Snake[0].x = START_POINT;
        Snake[0].y = START_POINT;
    }
}

void DrawSnake()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < CELL_SIZE; i++)
    {
        for (int j = 0; j < CELL_SIZE; j++)
        {
            DrawLine(0, (j + 1) * CELL_SIZE, SCREEN_SIZE, (j + 1) * CELL_SIZE, WHITE);
        }
        DrawLine((i + 1) * CELL_SIZE, 0, (i + 1) * CELL_SIZE, SCREEN_SIZE, WHITE);
    }
    for (int i = 0; i < snake_size; i++)
    {
        DrawRectangle(Snake[i].x, Snake[i].y, CELL_SIZE, CELL_SIZE, ((i == 0) ? HEAD_COLOR : TAIL_COLOR));
    }
    if (food_present)
        DrawRectangle(Food.x, Food.y, FOOD_SIZE, FOOD_SIZE, MAGENTA);

    DrawText(TextFormat("Score: %d", score), 20, 20, 30, RED);
    EndDrawing();
}