#pragma once
#include <string>
#include <vector>
#include <map>


namespace homer {
    
    class Entity;

    class IScene;

    class World final {
    public:
        ~World() = default;

        //utilisé par l'engin
        void Update(float dt);
        void Draw();

        //gestion des entity
        Entity* World::Create(const std::string& name);
        void Add(Entity* entity); //c'est que le world qui l'utilise on passe que pas Create
        void Remove(Entity* entity);
        Entity* Find(const std::string& name);

        //gestion des scenes
        void Register(const std::string& name, IScene* scene);
        void Load(const std::string& scene);

        //avant de load une scene je dois vider la scene courante s'il y'en a une
        void Unload();

    private:
        //entity 
        std::vector<Entity*> m_entityInWorld;
        std::map<std::string, Entity*> m_entityMap;

        //scene
        std::map<std::string, IScene*> m_scenes;
        IScene* m_currentScene = nullptr;
    };

}
