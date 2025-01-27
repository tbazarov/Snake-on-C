#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "food.h"
#include "snake.h"
#include "LVL.h"
#include "game_constants.h"

Rectangle GetCanvasTarget() 
{
  float sh = (float)GetScreenHeight();
  float sw = (float)GetScreenWidth();
  float scale = fminf(sh / CANVAS_HEIGHT, sw / CANVAS_WIDTH);
  Rectangle rec = {0, 0, CANVAS_WIDTH * scale, CANVAS_HEIGHT * scale};
  return rec;
}

void (*Draw)(void);
void (*Update)(void);

void GoToSelectLevel();
void GoToGame();

void Setup() 
{
  cool_down = 0;
  snake.dir_x = 1;
  snake.dir_y = 0;
  snake.next_dir_x = 1;
  snake.next_dir_y = 0;
  snake.length = 2;
  snake.pos_x = SNAKE_SPAWNS[current_lvl].x;
  snake.pos_y = SNAKE_SPAWNS[current_lvl].y;
  snake.last_step_updated_at = 0;
  snake.has_eaten = false;
  snake.speed = DIFFICULTY_SPEEDS[difficulty];
  is_game_over = false;
  for (int i = 0; i < FIELD_WIDTH; i++) 
  {
    for (int j = 0; j < FIELD_HEIGHT; j++) 
    {
      snake_body[i][j].lifetime = 0;
      snake_body[i][j].eat_inside = false;
    }
  }

  InitSnake();
  SpawnFood();
}

void DrawWallBody(int i, int j) 
{
  if (LVL[current_lvl][j][i] == 0) 
  {
    return;
  }

  DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
                WHITE);
}

void DrawGameMatrix() {
  for (int i = 0; i < FIELD_WIDTH; i++) 
  {
    for (int j = 0; j < FIELD_HEIGHT; j++) 
    {
      DrawSnakeBody(i, j);
      DrawWallBody(i, j);
    }
  }
  DrawSnakeHead();
}

void CheckCollisionWithWall() 
{
  if (LVL[current_lvl][snake.pos_y][snake.pos_x] > 0) 
  {
    is_game_over = true;
  }
}

void CheckTail() 
{
  if (snake_body[snake.pos_x][snake.pos_y].lifetime > 0) 
  {
    is_game_over = true;
  }
}

void DrawGame() 
{
  DrawFood();
  DrawGameMatrix();

  if (is_game_over) 
  {
    DrawText("You lose", 2, CANVAS_HEIGHT / 2, 20, MAGENTA);
    DrawText("Press F to restart", 2, CANVAS_HEIGHT / 2 + 20, 12, MAGENTA);
  }
}

void UpdateGame() 
{
  if (is_game_over) 
  {
    if (IsKeyPressed(KEY_F)) 
    {
      GoToSelectLevel();
    }
    return;
  }
  if (IsKeyPressed(KEY_R)) 
  {
    GoToSelectLevel();
    return;
  }


  MoveSnake();
  CheckFood();
  ControlSnake();
}

void GoToGame() 
{
  Draw = DrawGame;
  Update = UpdateGame;
  Setup();
}

void DrawSelectLevel() 
{
  DrawText("LEVEL: ", 4, 4, 20, MAGENTA);
  DrawText("press UP or Down", 4, 24, 12, MAGENTA);

  char buffer[3];  // max num is 99
  sprintf(buffer, "%d", current_lvl);
  DrawText(buffer, 84, 4, 20, MAGENTA);

  DrawText(DIFFICULTY_NAMES[difficulty], 4, 42, 20, MAGENTA);
  DrawText("press LEFT or RIGHT", 4, 62, 12, MAGENTA);

  DrawText("Press Enter to start", 4, 92, 12, MAGENTA);
}

void UpdateSelectLevel() 
{
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) 
  {
    current_lvl--;
  } 
  else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) 
  {
    current_lvl++;
  }
  if (current_lvl < 0) 
  {
    current_lvl = LVL_COUNT - 1;
  }
  if (current_lvl >= LVL_COUNT) 
  {
    current_lvl = 0;
  }

  if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) 
  {
    difficulty--;
  } 
  else if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) 
  {
    difficulty++;
  }
  if (difficulty < 0) 
  {
    difficulty = DIFFICULTY_COUNT - 1;
  }
  if (difficulty >= DIFFICULTY_COUNT) 
  {
    difficulty = 0;
  }

  if (IsKeyPressed(KEY_ENTER)) 
  {
    GoToGame();
  }
}

void GoToSelectLevel() 
{
  Draw = DrawSelectLevel;
  Update = UpdateSelectLevel;
}

void GameLoop() 
{
  BeginDrawing();
  ClearBackground(GREEN);

  BeginTextureMode(canvas);
  ClearBackground(BLACK);
  Draw();
  EndTextureMode();

  Rectangle canvas_field = {0, 0, (float)canvas.texture.width,
                            -(float)canvas.texture.height};
  DrawTexturePro(canvas.texture, canvas_field, GetCanvasTarget(), ZERO_VEC,
                 0.0f, WHITE);
  EndDrawing();
  Update();
}



