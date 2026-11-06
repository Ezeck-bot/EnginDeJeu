#include "../includes/Niveau1.h"
#include "Engine.h"
#include "World.h"
#include "Entity.h"
#include "TexteComponent.h"

void Niveau1::Load()
{
    //afficher le texte
    homer::Entity* intro = homer::Engine::Get()->world()->Create("intro");
    intro->AddComponent<TexteComponent>("Niveau 1");
}
