#pragma once
#include "Component.h"
#include "IUpdatable.h"

class BulletComponent : public homer::Component, public homer::IUpdatable {
public:
	BulletComponent(float speed = 300.0f, float lifetime = 1.0f);

	virtual void Update(float dt) override;

	void Fire(float dirX, float dirY);
private:
	float m_dirX = 0.0f;
	float m_dirY = 0.0f;
	float m_speed;
	float m_lifetime;      // durée de vie maximale
	float m_timer = 0.0f;
};