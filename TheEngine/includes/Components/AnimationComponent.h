#pragma once
#include <string>
#include <map>
#include "SpriteComponent.h"
#include "IUpdatable.h"

struct RectClip {
	int start = 0;
	int count = 0;
	float delay = 0.0f;
};

class AnimationComponent : public SpriteComponent, public homer::IUpdatable {
public:

	AnimationComponent(const std::string& filename);

	virtual ~AnimationComponent() = default;

	void InitAnimation(int frameInRows, int frameWidth, int frameHeight);
	void AddClip(const std::string& name, int start, int count, float delay);
	void Stop();
	void Play(const std::string& name, bool loop);

	virtual void Update(float dt) override;

	void SearchWidthHeightImage();

private:
	std::map<std::string, RectClip> m_clips;

	//
	int m_frameInRows = 0;
	int m_frameWidth = 0;
	int m_frameHeight = 0;

	// l'état de lecture
	std::string m_currentClip;
	int m_currentFrame = 0;
	float m_timer = 0.0f;
	bool m_loop = false;
	bool m_playing = false;
};