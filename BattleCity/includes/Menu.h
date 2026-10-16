#pragma once
#include "IScene.h"

class Menu : public homer::IScene {
public:
	virtual ~Menu() = default;

	virtual void Load() override;
};