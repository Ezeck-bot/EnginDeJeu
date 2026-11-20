#include "Engine.h"
#include "TexteComponent.h"

TexteComponent::TexteComponent(const std::string& texte) : m_texte(texte)
{

}

void TexteComponent::Start()
{
	m_fontId = homer::Engine::Get()->gfx()->LoadFont("Assets/Fonts/Inter-VariableFont.ttf", 20);
}

void TexteComponent::Draw()
{

    homer::Engine::Get()->gfx()->DrawString(
            m_texte,
            m_fontId, 
            0, 
            0, 
            { 0, 0, 255, 255 }
        );
}
