#ifndef FOOD
#define FOOD

//#pragma once
#include <stddef.h>

typedef struct Food_ {
  int x;
  int y;
} Food;

void SpawnFood();
void DrawFood();
void CheckFood();

#endif