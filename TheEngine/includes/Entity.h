#pragma once
#include <string>

class Entity {
public:
    Entity(const std::string& name) : m_name(name) {}
    virtual ~Entity() = default;

    virtual void Start() {}
    virtual void Update(float dt) {}
    virtual void Draw() {}
    virtual void Destroy() {}

    std::string& GetName() { return m_name; }

private:
    std::string m_name;
};