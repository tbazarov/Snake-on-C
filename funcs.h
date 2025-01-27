#ifndef FUNCS
#define FUNCS
//#pragma once
#include <stddef.h>

Rectangle GetCanvasTartet();
void Setup();
void DrawWallBody(int i, int j);
void CheckCollisionWithWall();
void CheckTail();
void GoToSelectLevel();
void UpdateSelectLevel();
void DrawSelectLevel();
void UpdateGame();
void DrawGame();
void DrawGameMatrix();
void GameLoop();

#endif






