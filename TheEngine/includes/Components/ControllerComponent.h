#pragma once
#include <AtlasComponent.h>
#include <AnimationComponent.h>

class ControllerComponent : public homer::Component, public homer::IUpdatable {
public:
	ControllerComponent();

	virtual ~ControllerComponent();

	virtual void Start() override;
	virtual void Update(float dt) override;

private:
	AtlasComponent* m_atlas = nullptr;
	AnimationComponent* m_animation = nullptr;

	//position de base, le player regarde en haut
	float m_dirX = 0.0f;
	float m_dirY = -1.0f;
};