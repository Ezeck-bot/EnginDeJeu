#include "../includes/Enemy.h"
#include <Engine.h>


Enemy::Enemy(const std::string& name) : Entity(name)
{

}

void Enemy::Start()
{
	m_textureEnemyId = homer::Engine::Get()->Gfx()->LoadTexture("Assets/Images/test2.png");
}

void Enemy::Update() {

}

void Enemy::Draw() {
	IGfx* _gfx = homer::Engine::Get()->Gfx();

	int w = 0, h = 0;
	_gfx->GetTextureSize(m_textureEnemyId, &w, &h);

	RectI src{ 0, 0, w, h };
	RectF dst{ m_x, m_y, 100.0f, 100.0f };

	_gfx->DrawTexture(m_textureEnemyId, src, dst, 0.0, Flip{ m_flipH, false }, Color{ 255, 255, 255, 255 });
}

void Enemy::Destroy() {

}