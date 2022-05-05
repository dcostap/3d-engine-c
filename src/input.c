#include "input.h"

SDL_EventType events[250];
int events_size = 0;

SDL_KeyCode keys_pressed[20];
int keys_pressed_size = 0;

SDL_KeyCode keys_released[20];
int keys_released_size = 0;

bool is_there_event(SDL_EventType event)
{
    for (int i = 0; i < events_size; i++)
    {
        if (events[i] == event)
            return true;
    }
    return false;
}

bool is_key_pressed(SDL_KeyCode key)
{
    for (int i = 0; i < keys_pressed_size; i++)
    {
        if (keys_pressed[i] == key)
            return true;
    }
    return false;
}

bool is_key_released(SDL_KeyCode key)
{
    for (int i = 0; i < keys_released_size; i++)
    {
        if (keys_released[i] == key)
            return true;
    }
    return false;
}

void reset_key_inputs()
{
    keys_released_size = 0;
    events_size = 0;
}

void update_key_inputs(SDL_Event e)
{
    if (events_size < ARRAY_LENGTH_STACK(keys_pressed))
    {
        events[events_size] = e.type;
        events_size++;
    }

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if (keys_pressed_size < ARRAY_LENGTH_STACK(keys_pressed))
        {
            keys_pressed[keys_pressed_size] = e.key.keysym.sym;
            keys_pressed_size++;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        SDL_KeyCode key = e.key.keysym.sym;
        for (int i = 0; i < keys_pressed_size; i++)
        {
            if (keys_pressed[i] == key)
            {
                if (keys_released_size < ARRAY_LENGTH_STACK(keys_released))
                {
                    keys_released[keys_released_size] = key;
                    keys_released_size++;
                }

                // displace the rest of the array 1 spot to the left
                if (i < keys_pressed_size - 1)
                {
                    for (int j = i; j < keys_pressed_size - 1; j++)
                    {
                        keys_pressed[j] = keys_pressed[j + 1];
                    }
                }
                keys_pressed_size--;
                break;
            }
        }
    }
}