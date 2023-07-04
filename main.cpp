#include <cstddef>
#include <iostream>
#include <math.h>
#include <raylib.h>

const size_t WINDOW_HEIGHT = 900;
const size_t WINDOW_WIDTH = 900;

const size_t PX_SIZE = 10;

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

enum States { Dead, Alive };
enum Direction { N, NE, E, SE, S, SW, W, NW };

void kill_except(size_t y, size_t x, Direction dir) {
  if (dir != N) {
    grid[y - 1][x] = Dead;
  }
  if (dir != NE) {
    grid[y - 1][x + 1] = Dead;
  }
  if (dir != E) {
    grid[y][x + 1] = Dead;
  }
  if (dir != SE) {
    grid[y + 1][x + 1] = Dead;
  }
  if (dir != S) {
    grid[y - 1][x] = Dead;
  }
  if (dir != SW) {
    grid[y - 1][x - 1] = Dead;
  }
  if (dir != W) {
    grid[y][x - 1] = Dead;
  }
  if (dir != NW) {
    grid[y - 1][x - 1] = Dead;
  }
}

void clear_grid(void) {
  for (size_t i = 0; i < HEIGHT; ++i) {
    for (size_t j = 0; j < WIDTH; ++j) {
      grid[i][j] = Dead;
    }
  }
}

bool is_alive(size_t x, size_t y, int mat[][HEIGHT]) {
  if (x < 0 || y < 0 || x >= HEIGHT || y >= WIDTH) {
    return false;
  }
  if (mat[x][y] == Alive) {
    return true;
  }
  return false;
}

int sur_cells[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1},
    // {-2, 0}, {-1, 1}, {0, 2}, {1, 1}, {2, 0}, {1, -1}, {0, -2}, {-1, -1},
};

void survive(void) {
  int temp[HEIGHT][WIDTH];
  for (size_t i = 0; i < HEIGHT; i += 1) {
    for (size_t j = 0; j < WIDTH; j += 1) {
      temp[i][j] = grid[i][j];
    }
  }

  for (size_t i = 0; i < HEIGHT; i += 1) {
    for (size_t j = 0; j < WIDTH; j += 1) {
      size_t count = 0;
      for (size_t k = 0; k < 8; ++k) {
        if (is_alive(i + sur_cells[k][0], j + sur_cells[k][1], temp)) {
          count++;
        }
      }
      if (is_alive(i, j, temp)) {
        if (count == 2 || count == 3) {
          grid[i][j] = Alive;
        } else {
          grid[i][j] = Dead;
        }
      } else {
        if (count == 3) {
          grid[i][j] = Alive;
        }
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
        if (grid[i][j] == Alive) {
          DrawRectangle(i * PX_SIZE, j * PX_SIZE, PX_SIZE, PX_SIZE,
                        Color{56, 229, 129, 255});
        } else {
          DrawRectangle(i * PX_SIZE, j * PX_SIZE, PX_SIZE, PX_SIZE,
                        Color{23, 28, 40, 255});
        }
      }
    }
    if (live) {
      survive();
    }
    WaitTime(0.1);
    EndDrawing();
  }

  return 0;
}
