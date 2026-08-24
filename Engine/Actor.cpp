#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "Texture.h"
#include "Math/MathUtils.h"
#include "Engine.h"
#include "Components/RendererComponent.h"
namespace nu {

    FACTORY_REGISTER(Actor)

    // lifespan
	
    Actor::Actor(const Actor& other) :
        // Copy stuff
        Object{ other },
        m_tag{ other.m_tag },
        m_transform{ other.m_transform },
        m_damping{ other.m_damping },
        m_lifespan{ other.m_lifespan } {
        // Clone all components
        for (const auto& component : other.m_components) {
            auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
            AddComponent(std::move(clone));
        }
    }

    // physics / acceleration
    void Actor::Update(float dt) {
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        for (auto& component : m_components) {
            component->Update(dt);
        }

        // physics
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / (1.0f + m_damping * dt);

        m_transform.position.x = math::Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = math::Wrap(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const nu::Renderer& renderer) const {

        for (auto& component : m_components) {
            // Check if component is a renderer component
            auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
            if (rendererComponent) {
                // draw renderer component
                rendererComponent->Draw(renderer);
            }
        }
    }

    float Actor::GetRadius() const {
        return 0.0f;
    }

    void Actor::Read(const json::value_t& value) {
        Object::Read(value);
        if (JSON_HAS_NAME(value, "transform")) {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "lifespan", m_lifespan);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);

        // Read actor components
        if (JSON_HAS_NAME(value, "components")) {
            // Iterate through components
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray()) {
                //Get component type
                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                std::cout << "Loading component type: " << typeName << std::endl;

                //Create component of type
                auto component = Factory::Instance().Create<Component>(typeName);

                if (component) {
                    component->Read(componentValue);
                    AddComponent(std::move(component));
                }
            }
        }
    }

    void Actor::AddComponent(std::unique_ptr<Component> component) {
        component->SetOwner(this);
        m_components.push_back(std::move(component));
    }
}