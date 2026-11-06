#pragma once
#include "Engine.h"
#include "Component.h"

class SpriteComponent : public homer::Component, public homer::IDrawable {
public:
	SpriteComponent(const std::string& filename);

	virtual ~SpriteComponent() = default;

	virtual void Start() override;
	virtual void Draw() override;

protected:
	std::string m_filename;
	size_t m_textureId = static_cast<size_t>(-1);
	RectI m_src{ 0, 0, 0, 0 };
	RectF m_size{ 0.0f, 0.0f, 0.0f, 0.0f };
};