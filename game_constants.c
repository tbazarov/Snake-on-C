#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "game_constants.h"

float cool_down = 0;
int current_lvl = 0;
bool is_game_over = false;
Food food = {-1, -1};

SnakeNode snake_body[FIELD_WIDTH][FIELD_HEIGHT];
Snake snake;

const Vector2 ZERO_VEC = {0, 0};
RenderTexture2D canvas;

const Coordinates SNAKE_SPAWNS[LVL_COUNT] = 
{
    {6, 6}, {6, 6}, {16, 4}, {4, 0}, {4, 0},
};

const int DIFFICULTY_COUNT = 3;
const char* const DIFFICULTY_NAMES[] = {"Difficulty: Loh", "Difficulty: Neploho", "Difficulty: Sigma"};
const float DIFFICULTY_SPEEDS[] = {0.2f, 0.1f, 0.05f}; // Скорости движения змейки 
int difficulty = 0;
float time_since_last_move = 0.0f;