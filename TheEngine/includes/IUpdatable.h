#pragma once
namespace homer {
    class IUpdatable {
    public:
        virtual ~IUpdatable() = default;
        virtual void Update(float dt) = 0;
    };
}