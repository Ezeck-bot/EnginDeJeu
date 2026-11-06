#pragma once
#include <string>
#include <vector>
#include <typeinfo>
#include <utility>
#include <type_traits> 
#include "IUpdatable.h"
#include "IDrawable.h"


namespace homer {   
    class Component;

    class Entity final {
    public:
        Entity(const std::string& name);
        virtual ~Entity();

        //template Add et Get
        template<typename T, typename... Args>
        T* AddComponent(Args&&... args){ //const std::string& texte
            T* cmp = new T(std::forward<Args>(args)...); //T* cmp = new T(texte);
            //&typeid(cmp);
            cmp->m_Entity = this;

            m_components.push_back(cmp);

            if (IUpdatable* u = dynamic_cast<IUpdatable*>(cmp)) {
                m_updatables.push_back(u);
            }

            if (IDrawable* d = dynamic_cast<IDrawable*>(cmp)) {
                m_drawables.push_back(d);
            }

            return cmp;
        }
        template <typename T> 
        T* GetComponent() {
            for (auto c : m_components) {
                if (T* found = dynamic_cast<T*>(c))
                {
                    return found;
                }
            }
            return nullptr;
        }

        void Start();
        void Update(float dt);
        void Draw();
        void Destroy();

        const std::string& GetName() { return m_Name; }


        //récuperer la position actuelle
        float GetX() const { return m_x; }
        float GetY() const { return m_y; }

        //changer la position la position
        void SetPositionX(float x) { m_x = x; }
        void SetPositionY(float y) { m_y = y; }

    private:
        std::string m_Name;
        std::vector<Component*> m_components;
        std::vector<IUpdatable*> m_updatables;
        std::vector<IDrawable*> m_drawables;

        //variable de position
        float m_x = 0.0f;
        float m_y = 0.0f;
    };


}