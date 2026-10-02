#pragma once

enum class Keys {
    Key_A,
    Key_B,
    Key_C,
    Key_D,
    Key_E,
    Key_F,
    Key_G,
    Key_H,
    Key_I,
    Key_J,
    Key_K,
    Key_L,
    Key_M,
    Key_N,
    Key_O,
    Key_P,
    Key_Q,
    Key_R,
    Key_S,
    Key_T,
    Key_U,
    Key_V,
    Key_W,
    Key_X,
    Key_Y,
    Key_Z,
};
class IInput {
public:
    virtual void Update() = 0;
    virtual bool IsKeyDown(int key) = 0;
    virtual bool IsButtonDown(int button) = 0;
    virtual void GetMousePosition(int* x, int* y) = 0;

	virtual ~IInput() = default;
};