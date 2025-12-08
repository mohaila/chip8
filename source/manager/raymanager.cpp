#include "raymanager.hpp"

RayManager::RayManager() {
  auto width = 10 * CHIP8_VIDEO_WIDTH;
  auto height = 10 * CHIP8_VIDEO_HEIGHT;

  InitWindow(width, height, "CHIP-8 Emulator");
  SetTargetFPS(60);
}

RayManager::~RayManager() { CloseWindow(); }

void RayManager::display(const int32_t* video) {
  Rectangle src = {
      .x = 0.0f,
      .y = 0.0f,
      .width = CHIP8_VIDEO_WIDTH,
      .height = CHIP8_VIDEO_HEIGHT,
  };

  Rectangle dst = {
      .x = 0.0f,
      .y = 0.0f,
      .width = 10.0f * CHIP8_VIDEO_WIDTH,
      .height = 10.0f * CHIP8_VIDEO_HEIGHT,
  };
  Vector2 origin{.x = 0.0f, .y = 0.0f};
  Image screen = {
      .data = (void*)video,
      .width = CHIP8_VIDEO_WIDTH,
      .height = CHIP8_VIDEO_HEIGHT,
      .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
      .mipmaps = 1,
  };
  auto texture = LoadTextureFromImage(screen);
  BeginDrawing();
  ClearBackground(BLACK);
  DrawTexturePro(texture, src, dst, origin, 0.0f, WHITE);
  EndDrawing();
  UnloadTexture(texture);
}

bool RayManager::handleKeys(bool* keys) {
  auto run = !WindowShouldClose();
  handleKeysUp(keys);
  handleKeysDown(keys);
  return run;
}

void RayManager::handleKeysUp(bool* keys) {
  if (IsKeyDown(KEY_KP_1)) {
    keys[0] = true;
  }
  if (IsKeyDown(KEY_KP_2)) {
    keys[1] = true;
  }
  if (IsKeyDown(KEY_KP_3)) {
    keys[2] = true;
  }
  if (IsKeyDown(KEY_KP_4)) {
    keys[3] = true;
  }
  if (IsKeyDown(KEY_Q)) {
    keys[4] = true;
  }
  if (IsKeyDown(KEY_W)) {
    keys[5] = true;
  }
  if (IsKeyDown(KEY_E)) {
    keys[6] = true;
  }
  if (IsKeyDown(KEY_R)) {
    keys[7] = true;
  }
  if (IsKeyDown(KEY_A)) {
    keys[8] = true;
  }
  if (IsKeyDown(KEY_S)) {
    keys[9] = true;
  }
  if (IsKeyDown(KEY_D)) {
    keys[10] = true;
  }
  if (IsKeyDown(KEY_F)) {
    keys[11] = true;
  }
  if (IsKeyDown(KEY_Z)) {
    keys[12] = true;
  }
  if (IsKeyDown(KEY_X)) {
    keys[13] = true;
  }
  if (IsKeyDown(KEY_C)) {
    keys[14] = true;
  }
  if (IsKeyDown(KEY_V)) {
    keys[15] = true;
  }
}

void RayManager::handleKeysDown(bool* keys) {
  if (IsKeyDown(KEY_KP_1)) {
    keys[0] = false;
  }
  if (IsKeyDown(KEY_KP_2)) {
    keys[1] = false;
  }
  if (IsKeyDown(KEY_KP_3)) {
    keys[2] = false;
  }
  if (IsKeyDown(KEY_KP_4)) {
    keys[3] = false;
  }
  if (IsKeyDown(KEY_Q)) {
    keys[4] = false;
  }
  if (IsKeyDown(KEY_W)) {
    keys[5] = false;
  }
  if (IsKeyDown(KEY_E)) {
    keys[6] = false;
  }
  if (IsKeyDown(KEY_R)) {
    keys[7] = false;
  }
  if (IsKeyDown(KEY_A)) {
    keys[8] = false;
  }
  if (IsKeyDown(KEY_S)) {
    keys[9] = false;
  }
  if (IsKeyDown(KEY_D)) {
    keys[10] = false;
  }
  if (IsKeyDown(KEY_F)) {
    keys[11] = false;
  }
  if (IsKeyDown(KEY_Z)) {
    keys[12] = false;
  }
  if (IsKeyDown(KEY_X)) {
    keys[13] = false;
  }
  if (IsKeyDown(KEY_C)) {
    keys[14] = false;
  }
  if (IsKeyDown(KEY_V)) {
    keys[15] = false;
  }
}