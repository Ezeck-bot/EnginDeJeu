#pragma once
#include "IInput.h"

class SDLInput final : public IInput {
public:
    virtual ~SDLInput() = default;
    virtual void Update() override;
    virtual bool IsKeyDown(int keycode) override;
    virtual bool IsButtonDown(int button) override;
    virtual void GetMousePosition(int* x, int* y) override;

private:
    const unsigned char* m_KeyStates = nullptr;
    int m_MouseX = 0;
    int m_MouseY = 0;
    bool m_MouseStates[3]{ false, false, false };
};