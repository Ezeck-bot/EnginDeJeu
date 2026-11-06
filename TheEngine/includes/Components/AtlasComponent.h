#pragma once
#include <string>
#include <map>
#include "SpriteComponent.h"

class AtlasComponent : public SpriteComponent {
public:
	AtlasComponent(const std::string& filename);

	virtual ~AtlasComponent() = default;

	void AddFrame(const std::string& name, int x, int y, int w, int h);

	void SetFrame(const std::string& name);

private:
	std::map<std::string, RectI> m_frames;

};