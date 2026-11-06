#include "Engine.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(const std::string& filename): m_filename(filename)
{
}

void SpriteComponent::Start()
{
	m_textureId = homer::Engine::Get()->gfx()->LoadTexture(m_filename);

	//cherche la taille réelle de l'image
	int w = 0, h = 0;
	homer::Engine::Get()->gfx()->GetTextureSize(m_textureId, &w, &h);

	// si je suis ici et que la taillle et la hauteur ont pas changés je mets les valeurs réelle
	if (m_src.w == 0 || m_src.h == 0)
	{
		m_src = RectI{ 0, 0, w, h };
	}
	if (m_size.w == 0.0f || m_size.h == 0.0f)
	{
		m_size.w = (float)(w);
		m_size.h = (float)(h);
	}

	//pour animation

}

void SpriteComponent::Draw()
{
	RectF _dst{
		(float)(m_Entity->GetX()),
		(float)(m_Entity->GetY()),
		m_size.w,
		m_size.h
	};

	//affichage du service
	homer::Engine::Get()->gfx()->DrawTexture(m_textureId, m_src, _dst, 0.0, Flip{ false, false }, Color{ 255, 255, 255, 255 });
}
