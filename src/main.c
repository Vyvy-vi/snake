#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

//////#define PLATFORM_WEB 1
#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

typedef struct node
{
    int x;
    int y;
} node;

#define SCREEN_SIZE 600
#define CELL_SIZE 30
#define FOOD_SIZE 15

#define HEAD_COLOR CLITERAL(Color) { 253, 249, 0, 255 }
#define TAIL_COLOR CLITERAL(Color) { 243, 255, 107, 255 }
#define FOOD_COLOR MAGENTA
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define GRID 0
const int FOOD_SPACING = ((CELL_SIZE - FOOD_SIZE) / 2);
const int START_POINT = SCREEN_SIZE / 2;

long max_score = 0;
node Snake[(SCREEN_SIZE * SCREEN_SIZE) / (CELL_SIZE * CELL_SIZE)];
int snake_size;
bool food_present;
node Food;
node offset;

void UpdateDrawFrame(void);
void ResetState(void);
void _ReadMaxScore(void);
void _WriteScore(long);
void _DrawGrid(void);

void ResetState()
{

    #if !defined(PLATFORM_WEB) 
      _WriteScore((snake_size - 1) * 10);
    #endif
    
    snake_size = 1;
    Snake[0].x = START_POINT;
    Snake[0].y = START_POINT;
    offset.x = 0;
    offset.y = 0;
    food_present = false;
}

int main(void)
{
    ResetState();
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Snake");
    #if defined(PLATFORM_WEB)
      emscripten_set_main_loop(UpdateDrawFrame, 10, 1);
    #else
      _ReadMaxScore();
      SetTargetFPS(8); 

    while (!WindowShouldClose())
    {
      UpdateDrawFrame();
    }
    #endif
    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
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

    // food collision
    if (food_present && Snake[0].x == Food.x - FOOD_SPACING && Snake[0].y == Food.y - FOOD_SPACING)
    {
        food_present = false;
        Snake[snake_size] = Snake[snake_size - 1];
        snake_size++;
    }

    // wall collision
    if (Snake[0].x < 0 || Snake[0].x > SCREEN_SIZE - CELL_SIZE || Snake[0].y < 0 || Snake[0].y > SCREEN_SIZE - CELL_SIZE) {
      ResetState();
    }


    // self collision
    for (int i = 1; i < snake_size - 1; i++)
    {
        if (Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y) {
          ResetState();
        }
    }

    max_score = MAX(max_score, (snake_size - 1) * 10);

    BeginDrawing();
    ClearBackground(BLACK);
    if (GRID)
      _DrawGrid();
    for (int i = 0; i < snake_size; i++)
    {
        DrawRectangle(Snake[i].x, Snake[i].y, CELL_SIZE, CELL_SIZE, ((i == 0) ? HEAD_COLOR : TAIL_COLOR));
    }
    if (food_present)
        DrawRectangle(Food.x, Food.y, FOOD_SIZE, FOOD_SIZE, FOOD_COLOR);

    DrawText(TextFormat("Score: %d", (snake_size - 1) * 10), 20, 20, 25, RED);
    DrawText(TextFormat("High-Score: %d", max_score), SCREEN_SIZE - (22 * (7 + snprintf(NULL, 0, "%ld", max_score))), 20, 25, RED);
    EndDrawing();

}


void _DrawGrid()
{
    for (int i = 0; i < CELL_SIZE; i++)
    {
        for (int j = 0; j < CELL_SIZE; j++)
        {
            DrawLine(0, (j + 1) * CELL_SIZE, SCREEN_SIZE, (j + 1) * CELL_SIZE, WHITE);
        }
        DrawLine((i + 1) * CELL_SIZE, 0, (i + 1) * CELL_SIZE, SCREEN_SIZE, WHITE);
    }
}

void _ReadMaxScore()
{
    FILE *file = fopen("build/scores.txt", "r");
    if (file == NULL)
        return;

    int num;
    while (fscanf(file, "%d", &num) > 0)
    {
        if (num > max_score)
            max_score = num;
    }
    fclose(file);
}

void _WriteScore(long score)
{
    FILE *file = fopen("build/scores.txt", "a");
    if (file == NULL)
        return;
    fprintf(file, "\n%ld", score);
    fclose(file);
}
