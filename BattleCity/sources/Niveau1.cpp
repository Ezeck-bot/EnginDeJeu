#include "../includes/Niveau1.h"
#include "../includes/Enemy.h"
#include <Engine.h>

void Niveau1::Load()
{
    Entity* e1 = new Enemy("enemy1");

    homer::Engine::Get()->WorlD()->Add(e1);
}
