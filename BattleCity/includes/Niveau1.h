#pragma once
#include "IScene.h"

class Niveau1 : public homer::IScene {
public:
	virtual ~Niveau1() = default;

	virtual void Load() override;
};