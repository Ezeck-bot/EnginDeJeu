#include "SDLInput.h"
#include "SDL.h"
#include "Engine.h"


void SDLInput::Update()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    SDL_Event _event;

    

    //SDL pool event est une queue
    while (SDL_PollEvent(&_event)) {
        switch (_event.type) {
        case SDL_QUIT:
            homer::Engine::Get()->Exit();
            break;
        case SDL_MOUSEMOTION:
        
            m_MouseX = _event.motion.x;
            m_MouseY = _event.motion.y;

            break;
        
        case SDL_MOUSEBUTTONDOWN:
            SDL_MouseButtonEvent _buttonDown = _event.button;


            if (_buttonDown.button < 3) m_MouseStates[_buttonDown.button] = true;
            m_MouseX = _buttonDown.x;
            m_MouseY = _buttonDown.y;

            break;

        case SDL_MOUSEBUTTONUP:
            SDL_MouseButtonEvent _buttonUp = _event.button;

            if (_buttonUp.button < 3) m_MouseStates[_buttonUp.button] = true;
            m_MouseX = _buttonUp.x;
            m_MouseY = _buttonUp.y;

            break;
        }
    }
}

int keys[] = {
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
};
bool SDLInput::IsKeyDown(int keycode)
{
	return m_KeyStates[keys[keycode]];
}

bool SDLInput::IsButtonDown(int button)
{
    if (button < 0 || button >= 3) return false;
    return m_MouseStates[button];
}

void SDLInput::GetMousePosition(int* x, int* y)
{
    if (x != nullptr && y != nullptr)
    {
        *x = m_MouseX;
        *y = m_MouseY;
    }
}
