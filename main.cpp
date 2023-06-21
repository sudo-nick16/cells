#include <iostream>
#include <math.h>
#include <raylib.h>

const size_t WINDOW_HEIGHT = 900;
const size_t WINDOW_WIDTH = 900;

const size_t PX_SIZE = 20;

const size_t HEIGHT = WINDOW_HEIGHT / PX_SIZE;
const size_t WIDTH = WINDOW_WIDTH / PX_SIZE;

size_t grid[HEIGHT][WIDTH] = {0};

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

void random_grid(void) {
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      grid[i][j] = (size_t)(rand_float() * 10) % 2;
    }
  }
}

void print_grid(void) {
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void clear_grid(void) {
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      grid[i][j] = 0;
    }
  }
}

void survive(void) {
  for (size_t i = 2; i < HEIGHT - 2; i += 1) {
    for (size_t j = 2; j < WIDTH - 2; j += 1) {
      size_t count = 0;
      if (grid[i - 2][j])
        count++;
      if (grid[i - 1][j + 1])
        count++;
      if (grid[i][j + 2])
        count++;
      if (grid[i + 1][j + 1])
        count++;
      if (grid[i + 2][j])
        count++;
      if (grid[i + 1][j - 1])
        count++;
      if (grid[i][j - 2])
        count++;
      if (grid[i - 1][j - 1])
        count++;

      if (count == 3 && grid[i][j] == 0) {
        grid[i][j] = 1;
      } else if ((count == 2 || count == 3) && grid[i][j] == 1) {
        grid[i][j] = 1;
      } else {
        grid[i][j] = 0;
      }
    }
  }
}

int main(void) {
  std::cout << "hello everyone";
  srand(time(0));

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cells");

  bool live = false;

  while (!WindowShouldClose()) {
    BeginDrawing();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      size_t x = GetMouseX();
      size_t y = GetMouseY();
      if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
        continue;
      grid[x / PX_SIZE][y / PX_SIZE] = 1;
    }

    if (IsKeyPressed(KEY_RIGHT_ALT)) {
      live = false;
      clear_grid();
    }

    if (IsKeyPressed(KEY_SPACE)) {
      live = !live;
    }

    for (size_t i = 0; i < HEIGHT; i += 1) {
      for (size_t j = 0; j < WIDTH; j += 1) {
        if (grid[i][j] == 1) {
          DrawRectangle(i * PX_SIZE, j * PX_SIZE, PX_SIZE, PX_SIZE,
                        Color{56, 229, 129, 255});
        } else {
          DrawRectangle(i * PX_SIZE, j * PX_SIZE, PX_SIZE, PX_SIZE,
                        Color{23, 28, 40, 255});
        }
      }
    }
    WaitTime(0.01);
    if (live) {
      survive();
    }
    EndDrawing();
  }

  return 0;
}
