#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

void DrawGame(void);
void UpdateGame(void);

#define CELL_SIZE 30
#define FOOD_SIZE 30

const int screenWidth = 600;

int score = 0;

typedef struct node
{
    int x;
    int y;
} node;

node Snake[(screenWidth * screenWidth) / (CELL_SIZE * CELL_SIZE)];
int snake_size = 1;
bool food_present = false;
bool add_tail = false;
node Tail;
node Food;

int main(void)
{
    InitWindow(screenWidth, screenWidth, "Snake");
    Snake[0].x = screenWidth / 2;
    Snake[0].y = screenWidth / 2;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        DrawGame();
        UpdateGame();
    }

    CloseWindow();

    return 0;
}

void UpdateGame()
{
    if (!food_present)
    {
        Food.x = rand() % (screenWidth / CELL_SIZE) * CELL_SIZE;
        Food.y = rand() % (screenWidth / CELL_SIZE) * CELL_SIZE;
        food_present = true;
    }

    node offset;
    offset.x = 0;
    offset.y = 0;

    if (IsKeyPressed(KEY_RIGHT))
    {
        if (Snake[0].x == screenWidth)
            CloseWindow();
        offset.x = CELL_SIZE;
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        if (Snake[0].x == 0)
            CloseWindow();
        offset.x = -CELL_SIZE;
    }
    else if (IsKeyPressed(KEY_UP))
    {
        if (Snake[0].y == 0)
            CloseWindow();
        offset.y = -CELL_SIZE;
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        if (Snake[0].y == screenWidth)
            CloseWindow();
        offset.y = CELL_SIZE;
    }
    else
        return;

    for (int i = snake_size - 1; i > 0; i--)
        Snake[i] = Snake[i - 1];

    Snake[0].x += offset.x;
    Snake[0].y += offset.y;

    if (food_present && Snake[0].x == Food.x && Snake[0].y == Food.y)
    {
        food_present = false;
        snake_size++;
        score += 10;
    }
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < CELL_SIZE; i++)
    {
        for (int j = 0; j < CELL_SIZE; j++)
        {
            DrawLine(0, (j + 1) * CELL_SIZE, screenWidth, (j + 1) * CELL_SIZE, WHITE);
        }
        DrawLine((i + 1) * CELL_SIZE, 0, (i + 1) * CELL_SIZE, screenWidth, WHITE);
    }
    DrawText(TextFormat("Score: %d", score), 20, 20, 20, RAYWHITE);
    for (int i = 0; i < snake_size; i++)
    {
        DrawRectangle(Snake[i].x, Snake[i].y, CELL_SIZE, CELL_SIZE, YELLOW);
    }
    if (food_present)
        DrawRectangle(Food.x, Food.y, FOOD_SIZE, FOOD_SIZE, MAGENTA);
    EndDrawing();
}