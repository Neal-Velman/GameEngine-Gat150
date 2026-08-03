#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>

namespace nu {

    class Scene;

    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity { 0.0f, 0.0f };
        float damping { 0.0f };
        float lifespan { 0.0f };
        Model model;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& ActorDesc) : m_name{ ActorDesc.name }, m_tag{ ActorDesc.tag }, m_transform{ ActorDesc.transform }, m_velocity{ ActorDesc.velocity }, m_damping{ ActorDesc.damping }, m_lifespan{ ActorDesc.lifespan}, m_model{ ActorDesc.model } {}
        Actor(const Transform& transform) : m_transform{ transform } {}
        Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ model } {}

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const { return m_transform; }

        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const nu::Vector2& GetVelocity() { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }

        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }

        bool GetDestroyed() const { return m_destroyed; }

        friend Scene;

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        float m_damping{ 0.0f };
        float m_lifespan { 0.0f };
        bool m_destroyed { false };
        Model m_model;
        Scene* m_scene{ nullptr };
    };

}

