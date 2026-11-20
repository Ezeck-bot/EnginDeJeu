#include "Niveau1.h"
#include "Engine.h"
#include "Entity.h"
#include "TexteComponent.h"
#include "AtlasComponent.h"
#include "AnimationComponent.h"
#include "ControllerComponent.h"
#include <EnemyComponent.h>
#include <BulletComponent.h>

void Niveau1::Load()
{
    //afficher le texte
    homer::Entity* niveau1 = homer::Engine::Get()->world()->Create("niveau1");

    //Texte
    niveau1->AddComponent<TexteComponent>("Niveau 1 \n `WASD` pour bouger le player \n `F` pour tirer \n `K` pour Play la music \n `I` pour jouer un sfx \n `P` pour mettre pause a la musique \n `R` pour continuer la music \n `H` pour stop la music \n `J` Pour diminuer le volume \n `L` pour augmenter le volume");

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
