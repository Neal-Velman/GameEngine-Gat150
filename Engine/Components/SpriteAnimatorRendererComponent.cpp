#include "pch.h"
#include "SpriteAnimatorRendererComponent.h"
#include "Renderer/TextureFrames.h"
#include "Core/StringUtils.h"
#include "Engine.h"
#include "Core/Factory.h"

namespace nu {
	FACTORY_REGISTER(SpriteAnimatorRendererComponent)

	void SpriteAnimatorRendererComponent::Start() {
		if (!m_defaultAnimationName.empty()) {
			Play(m_defaultAnimationName);
		} else {
			// Default to first element in map
			auto iter = m_spriteAnimations.begin();
			std::string name = iter->first;
			Play(name);
		}
	}

	void SpriteAnimatorRendererComponent::Update(float dt) {
		if (!m_spriteAnimation.textureFrames) { return; }

		m_frameTimer += dt;
		float frameTime = 1.0f / m_spriteAnimation.framesPerSecond;

		//Increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime) {
			m_frame++;
			if (m_spriteAnimation.loop) {
				// Loop frames if loop is true
				m_frame = m_frame % m_spriteAnimation.textureFrames->GetTotalFrames();
				// m_frame = Wrap(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);
			}
			else {
				// m_frame = Clamp(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);
				if (m_frame >= (m_spriteAnimation.textureFrames->GetTotalFrames() - 1)) {
					// if loop isn't true, then stop it at the last frame
					m_frame = m_spriteAnimation.textureFrames->GetTotalFrames() - 1;
				}
			}
			m_frameTimer -= frameTime;
		}
		m_sourceRect = m_spriteAnimation.textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimatorRendererComponent::Play(const std::string name) {
		auto iter = m_spriteAnimations.find(ToLower(name));
		if (iter == m_spriteAnimations.end()) {
			std::cerr << "Couldn't find animation: " << name << std::endl;
			return;
		}
		m_spriteAnimation = iter->second;

		m_frame = 0;
		m_frameTimer = 0.0f;

		m_texture = m_spriteAnimation.textureFrames->GetTexture();
		m_sourceRect = m_spriteAnimation.textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimatorRendererComponent::Read(const json::value_t& value) {
		SpriteRendererComponent::Read(value);

		JSON_READ_NAME(value, "default_animation", m_defaultAnimationName);

		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray())
		{
			for (auto& animatorValue : JSON_GET(value, animations).GetArray())
			{
				SpriteAnimation spriteAnimation;

				std::string textureAnimationName;

				JSON_READ_NAME(animatorValue, "name", spriteAnimation.name);

				std::string texture_frames;
				JSON_READ_REQ(animatorValue, texture_frames);

				if (!texture_frames.empty())
				{
					spriteAnimation.textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
					if (!spriteAnimation.textureFrames)
					{
						std::cerr << "Could not load texture frames: " << texture_frames << std::endl;
					}
				}

				JSON_READ_NAME_REQ(animatorValue, "frames_per_second", spriteAnimation.framesPerSecond);
				JSON_READ_NAME(animatorValue, "loop", spriteAnimation.loop);

				m_spriteAnimations[ToLower(spriteAnimation.name)] = spriteAnimation;
			}
		}

	}
}

