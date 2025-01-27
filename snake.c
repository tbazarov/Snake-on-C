#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

#include "snake.h"
#include "funcs.h"
//#include "LVL.h"
#include "game_constants.h"


void InitSnake() 
{
  for (int i = 0; i < snake.length; i++) 
  {
    int x = snake.pos_x - snake.dir_x * i;
    int y = snake.pos_y - snake.dir_y * i;
    snake_body[x][y].lifetime = snake.length - i;
  }
}

void DrawSnakeBody(int i, int j) 
{
  if (snake_body[i][j].lifetime < 1) 
  {
    return;
  }

  DrawRectangle(i * CELL_WIDTH, j * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT,
                GOLD);
}

void DrawSnakeHead() 
{
  DrawRectangle(snake.pos_x * CELL_WIDTH, snake.pos_y * CELL_HEIGHT, CELL_WIDTH,
                CELL_HEIGHT, BROWN);
}



void MoveSnake() 
{
    // Обновляем время с последнего движения
    time_since_last_move += GetFrameTime();

    // Проверяем, достаточно ли времени прошло для следующего шага
    if (time_since_last_move < snake.speed) 
    {
        return; // Если нет, выходим из функции
    }

    // Сбрасываем таймер
    time_since_last_move = 0.0f;

    // Обновляем положение змейки в каждом кадре
    snake.pos_x += snake.dir_x;
    snake.pos_y += snake.dir_y;

    // Обработка выхода за границы поля
    if (snake.pos_x >= FIELD_WIDTH) 
    {
        snake.pos_x = 0;
    }
    if (snake.pos_x < 0) 
    {
        snake.pos_x = FIELD_WIDTH - 1;
    }
    if (snake.pos_y >= FIELD_HEIGHT) 
    {
        snake.pos_y = 0;
    }
    if (snake.pos_y < 0) 
    {
        snake.pos_y = FIELD_HEIGHT - 1;
    }

    // Проверка на хвост
    CheckTail();
    
    // Проверка на столкновение со стеной
    CheckCollisionWithWall();
    
    // Установка времени жизни сегмента хвоста
    snake_body[snake.pos_x][snake.pos_y].lifetime = snake.length;

    // Уменьшаем время жизни сегментов хвоста, если змея не съела еду
    if (!snake.has_eaten) 
    {
        for (int i = 0; i < FIELD_WIDTH; i++) 
        {
            for (int j = 0; j < FIELD_HEIGHT; j++) 
            {
                if (snake_body[i][j].lifetime > 0) 
                {
                    snake_body[i][j].lifetime--;
                }
            }
        }
    } 
    else 
    {
        snake.has_eaten = false;
    }
}


void ControlSnake() 
{
    // Управление направлением змейки без задержки
    if ((snake.dir_y == 0) && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))) 
    {
        snake.next_dir_y = -1;
        snake.next_dir_x = 0;
    }
    else if ((snake.dir_y == 0) && (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))) 
    {
        snake.next_dir_y = 1;
        snake.next_dir_x = 0;
    }
    else if ((snake.dir_x == 0) && (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))) 
    {
        snake.next_dir_y = 0;
        snake.next_dir_x = -1;
    }
    else if ((snake.dir_x == 0) && (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))) 
    {
        snake.next_dir_y = 0;
        snake.next_dir_x = 1;
    }

    // Обновляем текущее направление только если новое направление не противоположно текущему
    if ((snake.next_dir_x != -snake.dir_x || snake.next_dir_y != -snake.dir_y)) 
    {
        snake.dir_x = snake.next_dir_x;
        snake.dir_y = snake.next_dir_y;
    }
}



