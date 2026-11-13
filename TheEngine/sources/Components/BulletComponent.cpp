#include "BulletComponent.h"
#include "Entity.h"

BulletComponent::BulletComponent(float speed, float lifetime) : m_speed(speed), m_lifetime(lifetime)
{
}

void BulletComponent::Update(float dt)
{
	m_timer += dt;

	if (m_timer >= m_lifetime)
	{
		m_Entity->SetActive(false);
		return;
	}

	m_Entity->SetPositionX(m_Entity->GetX() + m_dirX * m_speed * dt);
	m_Entity->SetPositionY(m_Entity->GetY() + m_dirY * m_speed * dt);
	
}


void BulletComponent::Fire(float dirX, float dirY)
{
	m_dirX = dirX;
	m_dirY = dirY;
	m_timer = 0.0f;
}
