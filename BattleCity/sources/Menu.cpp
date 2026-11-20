#include "Menu.h"
#include "Engine.h"
#include "Entity.h"
#include "TexteComponent.h"
#include "AtlasComponent.h"
#include "AnimationComponent.h"
#include "ControllerComponent.h"
#include "EnemyComponent.h"
#include "BulletComponent.h"
#include "TiledComponent.h"



void Menu::Load() {

    // map 
    homer::Entity* map = homer::Engine::Get()->world()->Create("Map");
    map->AddComponent<TiledComponent>("Assets/Map/map_test.tmx", 2.4f);

    //Le world crée l'entity menu
    homer::Entity* menu = homer::Engine::Get()->world()->Create("Menu");

    //texte scene
    menu->AddComponent<TexteComponent>("Menu \n `E` pour stop anim \n `WASD` pour bouger le player \n `F` pour tirer \n `Espace` pour changer de scene");
    
    //chargé l'image et affiché la partie qui le concerne pour le player
    homer::Entity* player = homer::Engine::Get()->world()->Create("player");

    AtlasComponent* image_player = player->AddComponent<AtlasComponent>("Assets/Images/Player.png");

    image_player->AddFrame("haut", 0, 0, 26, 32);
    image_player->AddFrame("droite", 32, 0, 26, 32);
    image_player->AddFrame("bas", 64, 0, 26, 32);
    image_player->AddFrame("gauche", 96, 0, 26, 32);
    image_player->SetFrame("haut");

    //position de depart
    player->SetPositionX(450);
    player->SetPositionY(550);

    //animation
    AnimationComponent* anim = player->AddComponent<AnimationComponent>("Assets/Images/effects.png");
    anim->InitAnimation(2, 32, 32);
    anim->AddClip("effet", 0, 2, 0.3f);
    anim->Play("effet", true);

    //activer les controller
    player->AddComponent<ControllerComponent>();

    //----ENEMY
    homer::Entity* enemy1 = homer::Engine::Get()->world()->Create("Enemy1");

    AtlasComponent* enemy_position = enemy1->AddComponent<AtlasComponent>("Assets/Images/Enemy.png");
    enemy_position->AddFrame("haut", 0, 0, 32, 32);
    enemy_position->AddFrame("droite", 32, 0, 32, 32);
    enemy_position->AddFrame("bas", 64, 0, 32, 32);
    enemy_position->AddFrame("gauche", 96, 0, 32, 32);
    enemy_position->SetFrame("bas");

    //position de depart
    enemy1->SetPositionX(450);

    enemy1->AddComponent<EnemyComponent>();

    
    //Bullet
    homer::Entity* bullet = homer::Engine::Get()->world()->Create("Bullet");
    AtlasComponent* image_bullet = bullet->AddComponent<AtlasComponent>("Assets/Images/Bullet2.png");
    image_bullet->AddFrame("haut", 0, 0, 6, 7);
    image_bullet->AddFrame("droite", 7, 0, 6, 7);
    image_bullet->AddFrame("bas", 14, 0, 6, 7);
    image_bullet->AddFrame("gauche", 22, 0, 6, 7);

    bullet->AddComponent<BulletComponent>();
    bullet->SetActive(false);

    
}