#pragma once
#include "Entity.h"

class Enemy final : public Entity {
public:

    Enemy(const std::string& name);
    virtual ~Enemy() = default;

    virtual void Start();
    virtual void Update();
    virtual void Draw();
    virtual void Destroy();

    void SetX(float x) { m_x = x; }
    void SetY(float y) { m_y = y; }

private:
    float m_x = 0.0f;
    float m_y = 0.0f;

    size_t m_textureEnemyId = 0;
    bool m_flipH = false;
};