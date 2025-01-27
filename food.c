#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "food.h"
#include "funcs.h"
#include "LVL.h"


void SpawnFood() 
{
  
  int x;
  int y;
  do {
    x = GetRandomValue(0, FIELD_WIDTH - 1);
    y = GetRandomValue(0, FIELD_HEIGHT - 1);
  } while (snake_body[x][y].lifetime > 0 || LVL[current_lvl][y][x] > 0);
  TraceLog(LOG_INFO, "Spawn food at [%d,%d]", x, y);
  food.x = x;
  food.y = y;
}


void DrawFood() {
  int dw = (CELL_WIDTH - EAT_WIDTH) / 2;
  int dh = (CELL_HEIGHT - EAT_HEIGHT) / 2;
  DrawRectangle(food.x * CELL_WIDTH + dw, food.y * CELL_HEIGHT + dh, EAT_HEIGHT,
                EAT_WIDTH, MAROON);
}

void CheckFood() {
  if (snake.pos_x == food.x && snake.pos_y == food.y) 
  {
    snake.length++;
    snake.has_eaten = true;
    SpawnFood();
  }
}
