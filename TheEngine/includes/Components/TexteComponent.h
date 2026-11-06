#pragma once
#include "Component.h"
#include "IDrawable.h"

class TexteComponent : public homer::Component, public homer::IDrawable {
public :
    TexteComponent(const std::string& texte);
    virtual void Start() override;
    virtual void Draw() override;

private:
    std::string m_texte;
    size_t m_fontId = 0;
};