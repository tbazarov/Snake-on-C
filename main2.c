#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "LVL.h"
// #include "food.h"
// #include "snake.h"
#include "funcs.h"
#include "game_constants.h"


int main() 
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(CANVAS_WIDTH * 2, CANVAS_HEIGHT * 2, "Snake");
  SetTargetFPS(30);
  SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);
  canvas = LoadRenderTexture(CANVAS_WIDTH, CANVAS_HEIGHT);
  SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);

  Setup();
  GoToSelectLevel();

  while (!WindowShouldClose()) 
  {
    GameLoop();
  }


  CloseWindow();

  return 0;
}