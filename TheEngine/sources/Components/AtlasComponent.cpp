#include "AtlasComponent.h"


AtlasComponent::AtlasComponent(const std::string& filename) : SpriteComponent(filename)
{
}

void AtlasComponent::AddFrame(const std::string& name, int x, int y, int w, int h)
{
	m_frames[name] = RectI{ x, y, w, h };
}

void AtlasComponent::SetFrame(const std::string& name)
{
    if (m_frames.count(name) == 0) {
        return;
    }

    m_src = m_frames.at(name);

    //imposer les valeurs car l'image prend toute l'espace
    m_size.w = (float)(m_src.w);
    m_size.h = (float)(m_src.h);
}
