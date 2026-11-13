#include "Menu.h"
#include "Engine.h"
#include "Entity.h"
#include "TexteComponent.h"
#include <AtlasComponent.h>
#include <AnimationComponent.h>
#include <ControllerComponent.h>
#include <EnemyComponent.h>
#include <BulletComponent.h>



void Menu::Load() {
    //Le world crée l'entity menu
    homer::Entity* menu = homer::Engine::Get()->world()->Create("Menu");

    //texte scene
    menu->AddComponent<TexteComponent>("Menu");
    
    //chargé l'image et affiché la partie qui le concerne
    AtlasComponent* player = menu->AddComponent<AtlasComponent>("Assets/Images/Player.png");

    player->AddFrame("haut", 0, 0, 26, 32);
    player->AddFrame("droite", 32, 0, 26, 32);
    player->AddFrame("bas", 64, 0, 26, 32);
    player->AddFrame("gauche", 96, 0, 26, 32);
    //position initiale
    player->SetFrame("haut");

    //animation
    AnimationComponent* anim = menu->AddComponent<AnimationComponent>("Assets/Images/effects.png");
    anim->InitAnimation(2, 32, 32);
    anim->AddClip("effet", 0, 2, 0.3f);
    anim->Play("effet", true);

    //activer les controller
    menu->AddComponent<ControllerComponent>();

    //----ENEMY
    homer::Entity* enemy1 = homer::Engine::Get()->world()->Create("Enemy1");

    AtlasComponent* enemy_position = enemy1->AddComponent<AtlasComponent>("Assets/Images/Enemy.png");
    enemy_position->AddFrame("haut", 0, 0, 32, 32);
    enemy_position->AddFrame("droite", 32, 0, 32, 32);
    enemy_position->AddFrame("bas", 64, 0, 32, 32);
    enemy_position->AddFrame("gauche", 96, 0, 32, 32);
    enemy_position->SetFrame("bas");

    enemy1->AddComponent<EnemyComponent>();

    
    //Bullet
    homer::Entity* bullet = homer::Engine::Get()->world()->Create("Bullet");
    AtlasComponent* image_bullet = bullet->AddComponent<AtlasComponent>("Assets/Images/Bullet2.png");
    image_bullet->AddFrame("haut", 0, 0, 6, 7);
    image_bullet->AddFrame("droite", 7, 0, 6, 7);
    image_bullet->AddFrame("bas", 14, 0, 6, 7);
    image_bullet->AddFrame("gauche", 22, 0, 6, 7);
    //position initiale
    //image_bullet->SetFrame("haut");


    bullet->AddComponent<BulletComponent>();
    bullet->SetActive(false);
}