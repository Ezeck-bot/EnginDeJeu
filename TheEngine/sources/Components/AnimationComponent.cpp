#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(const std::string& filename) : SpriteComponent(filename)
{
}

void AnimationComponent::InitAnimation(int frameInRows, int frameWidth, int frameHeight)
{
	m_frameInRows = frameInRows;
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
}

void AnimationComponent::AddClip(const std::string& name, int start, int count, float delay)
{
	m_clips[name] = RectClip{ start, count, delay };
}

void AnimationComponent::Stop()
{
	m_playing = false;
}

void AnimationComponent::Play(const std::string& name, bool loop)
{
	m_currentClip = name;
	m_loop = loop;

	m_currentFrame = 0;
	m_timer = 0.0f;
	m_playing = true;

	SearchWidthHeightImage();
}

void AnimationComponent::Update(float dt)
{

	if (!m_playing)
	{
		return;
	}

	m_timer += dt;

	while (m_timer >= m_clips.at(m_currentClip).delay)
	{
		m_timer = m_timer - m_clips.at(m_currentClip).delay;
		m_currentFrame++;

		if (m_currentFrame >= m_clips.at(m_currentClip).count)
		{
			if (m_loop)
			{
				m_currentFrame = 0;
			}
			else
			{
				m_currentFrame = m_clips.at(m_currentClip).count - 1;
				m_playing = false;
				break;
			}
		}
	}

	SearchWidthHeightImage();
}

void AnimationComponent::SearchWidthHeightImage()
{
	int _frame = m_clips.at(m_currentClip).start + m_currentFrame;

	int _col = _frame % m_frameInRows;
	int _row = _frame / m_frameInRows;

	m_src = RectI{ _col * m_frameWidth, _row * m_frameHeight, m_frameWidth, m_frameHeight };
	m_size.w = static_cast<float>(m_frameWidth);
	m_size.h = static_cast<float>(m_frameHeight);
}
