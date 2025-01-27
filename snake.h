#ifndef SNAKE
#define SNAKE
// #pragma once
#include <stddef.h>


typedef struct SnakeNode_ {
  int lifetime;
  bool eat_inside;
} SnakeNode;

typedef struct Snake_ {
  int dir_x;  
  int dir_y;  
  int next_dir_x;
  int next_dir_y;
  int length;
  int pos_x;
  int pos_y;
  float speed;                 
  float last_step_updated_at;  
  bool has_changed_dir;
  bool has_eaten;
} Snake;


void InitSnake();
void MoveSnake();
void DrawSnakeBody(int i, int j);
void DrawSnakeHead();
void ControlSnake(); 

#endif


