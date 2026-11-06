#pragma once
#include <AtlasComponent.h>
#include <AnimationComponent.h>

class EnemyComponent : public homer::Component, public homer::IUpdatable {
public:
	EnemyComponent();

	virtual ~EnemyComponent();

	virtual void Start() override;
	virtual void Update(float dt) override;

private:
	AtlasComponent* m_atlas = nullptr;
	AnimationComponent* m_animation = nullptr;

	bool m_movingLeft = false;
};