#pragma once
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Resources/Resource.h"
#include "Object.h"
#include "Components/Component.h"
#include <string>
#include <memory>


namespace nu {

    class Scene;
    class Texture;

    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity { 0.0f, 0.0f };
        float damping { 0.0f };
        float lifespan { 0.0f };
        res_t<Model> model;
        res_t<Texture> texture;
    };

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const ActorDesc& ActorDesc) : m_tag{ ActorDesc.tag }, m_transform{ ActorDesc.transform },
            m_lifespan{ ActorDesc.lifespan } {}
        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void Start();
        virtual void OnDestroy();

        virtual void OnCollision(Actor* other) {}

        const Transform& GetTransform() const { return m_transform; }
        void SetTransform(const Transform& transform) { m_transform = transform; }

        void SetPosition(const Vector2& position) { m_transform.position = position; }
        const Vector2 GetPosition() const { return m_transform.position; }

        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        const Vector2 GetRotation() const { return m_transform.rotation; }

        void SetScale(float scale) { m_transform.scale = scale; }
        const Vector2 GetScale() const { return m_transform.scale; }

        const std::string& GetName() const { return m_name; }

        void SetTag(const std::string& tag) { m_tag = tag; }
        const std::string& GetTag() const { return m_tag; }

        Scene* GetScene() { return m_scene; }

        float GetRadius() const;

        void SetDestroyed(bool destroy = true) { m_destroyed = destroy; }
        bool GetDestroyed() const { return m_destroyed; }

        bool GetPersistent() const { return m_persistent; }

        virtual void Read(const json::value_t& value) override;

        void AddComponent(std::unique_ptr<Component> component);

        template<std::derived_from<Component> T>
        T* GetComponent();

        friend Scene;

    protected:
        std::string m_tag;

        Transform m_transform;
        float m_lifespan { 0.0f };
        bool m_destroyed { false };
        bool m_persistent{ false };

        std::vector<std::unique_ptr<Component>> m_components;

        Scene* m_scene{ nullptr };
    };

    template<std::derived_from<Component> T>
    inline T* Actor::GetComponent() {
        for (auto& component : m_components) {
            auto result = dynamic_cast<T*>(component.get());
            if (result) {
                return result;
            }
        }
        return nullptr;
    }
}

