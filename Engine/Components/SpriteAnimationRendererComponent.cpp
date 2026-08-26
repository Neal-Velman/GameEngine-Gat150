#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Core/Factory.h"
#include "Engine.h"
#include "Renderer/TextureFrames.h"

namespace nu {
	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt) {
		if (!m_textureFrames) { return; }

		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSecond;

		//Increase frame while frame timer is greater than frame time
		while (m_frameTimer >= frameTime) {
			m_frame++;
			if (m_loop) {
				// Loop frames if loop is true
				m_frame = m_frame % m_textureFrames->GetTotalFrames();
				// m_frame = Wrap(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);
			}
			else {
				// m_frame = Clamp(0u, m_textureFrames->GetTotalFrames() - 1, m_frame);
				if (m_frame >= (m_textureFrames->GetTotalFrames() - 1)) {
					// if loop isn't true, then stop it at the last frame
					m_frame = m_textureFrames->GetTotalFrames() - 1;
				}
			}

			m_frameTimer -= frameTime;
		}
	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer) {
		if (!m_textureFrames) {
			std::cerr << "Could not find a pointer for Texture Frames: " << m_textureFrames << std::endl;
			return; 
		}
		auto transform = GetOwner()->GetTransform();
		renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			m_textureFrames->GetFrameRect(m_frame),
			transform.position.x,
			transform.position.y,
			transform.rotation,
			transform.scale
		);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value) {
		RendererComponent::Read(value);
		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSecond);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;
		JSON_READ_REQ(value, texture_frames);

		if (!texture_frames.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
			if (!m_textureFrames) {
				std::cerr << "Couldn't load texture frames: " << texture_frames << std::endl;
			}
		}
	}
}