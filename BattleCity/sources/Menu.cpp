#include "../includes/Menu.h"
#include "../includes/Enemy.h"
#include <Engine.h>



void Menu::Load() {
    Entity* e1 = new Enemy("enemy1");
    
    homer::Engine::Get()->WorlD()->Add(e1);
}