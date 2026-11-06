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
};