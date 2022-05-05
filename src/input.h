#pragma once

#include "engine.h"

bool is_key_pressed(SDL_KeyCode key);
bool is_key_released(SDL_KeyCode key);
void reset_key_inputs();
void update_key_inputs(SDL_Event e);
bool is_there_event(SDL_EventType event);