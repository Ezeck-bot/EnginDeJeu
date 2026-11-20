#include "World.h"
#include <Entity.h>
#include <IScene.h>

namespace homer {
    World::~World()
    {
        Unload();
        for (auto scene : m_scenes) {
            if(scene.second) delete scene.second;
        }
    }
    void World::Update(float dt)
    {
        for (auto entity : m_entityInWorld) {
            entity->Update(dt);
        }
    }

    void World::Draw()
    {
        for (auto entity : m_entityInWorld) {
            entity->Draw();
        }
    }


    //--
    void World::Add(Entity* entity)
    {
	    m_entityInWorld.emplace_back(entity);
	    m_entityMap.emplace(entity->GetName(), entity);
    }

    void World::Remove(Entity* entity)
    {
    }

    Entity* World::Create(const std::string& name)
    {
        Entity* _e = new Entity(name);
        Add(_e);
        return _e;
    }

    Entity* World::Find(const std::string& name)
    {
        if (m_entityMap.count(name) > 0) {
            return m_entityMap[name];
        }

        return nullptr;
    }

    //
    void World::Load(const std::string& scene)
    {
        if (m_scenes.count(scene) > 0) {
            Unload();
            m_currentScene = m_scenes[scene];
            m_currentScene->Load();

            //Quand je finis de Load la scene je charge les entity
            for (auto entity : m_entityInWorld) {
                entity->Start();
            }
        }
    }

    void World::Register(const std::string& name, IScene* scene)
    {
        if (m_scenes.count(name) == 0) {
            m_scenes[name] = scene;
        }
    }

    void World::Unload()
    {
        for (auto entity : m_entityInWorld) {
            entity->Destroy();
            delete entity;
        }
        m_entityInWorld.clear();
        m_entityMap.clear();
        m_currentScene = nullptr;
    }
}
