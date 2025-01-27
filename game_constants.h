#ifndef CONSTANTS
#define CONSTANTS
//#pragma once
#include <stddef.h>
#include <raylib.h>

#include "food.h"
#include "snake.h"

#define CANVAS_WIDTH 240
#define CANVAS_HEIGHT 120

#define CELL_WIDTH 10   // in pixels
#define CELL_HEIGHT 10  // in pixels

#define EAT_WIDTH 6
#define EAT_HEIGHT 6

#define FIELD_WIDTH 24   // (CANVAS_WIDTH / CELL_WIDTH)
#define FIELD_HEIGHT 12  // (CANVAS_HEIGHT / CELL_HEIGHT)

#define LVL_COUNT 5

#define COOL_DOWN_BEFORE_START 1  // in seconds

typedef struct Coordinates_ 
{
  int x;
  int y;
} Coordinates;



extern float cool_down;
extern int current_lvl;
extern bool is_game_over;
extern Food food;

extern SnakeNode snake_body[FIELD_WIDTH][FIELD_HEIGHT];
extern Snake snake;




extern const Vector2 ZERO_VEC;
extern RenderTexture2D canvas;

extern const Coordinates SNAKE_SPAWNS[LVL_COUNT];

extern const int DIFFICULTY_COUNT;
extern const char* const DIFFICULTY_NAMES[];
extern const float DIFFICULTY_SPEEDS[]; // Скорости движения змейки 
extern int difficulty;
extern float time_since_last_move; // Время, прошедшее с последнего движения

#endif