#pragma once

#include "engine.h"

bool is_key_pressed(SDL_KeyCode key);
bool is_key_released(SDL_KeyCode key);
void update_input();
bool is_there_event(SDL_EventType event);