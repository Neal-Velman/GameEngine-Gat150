#pragma once
#include "RendererComponent.h"
#include "Resources/ResourceManager.h"
namespace nu {

	class SpriteAnimationRendererComponent : public RendererComponent {
	public:
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)

		void Update(float dt) override;
		void Draw(const Renderer& renderer) override;
		void Read(const json::value_t& value) override;

		
	private:
		float m_framesPerSecond = 1.0f;
		bool m_loop = true;

		unsigned int m_frame;
		float m_frameTimer = 0.0f;

		res_t<class TextureFrames> m_textureFrames;

	};

}