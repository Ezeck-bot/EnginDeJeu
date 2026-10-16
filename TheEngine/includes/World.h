#pragma once
#include <string>
#include <vector>
#include <map>

class Entity;

namespace homer {

    class IScene;

    class World final {
    public:
        ~World() = default;

        //utilisé par l'engin
        void Update(float dt);
        void Draw();

        //gestion des entity
        void Add(Entity* entity);
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
