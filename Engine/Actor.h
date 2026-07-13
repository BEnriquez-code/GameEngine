#pragma once
#include "Transform.h"
namespace nu {
    class Actor {
    public:
        Actor() = default;
        Actor(const Transform& transform) : m_transform{ transform } {}

        void Update(float dt);
        void Draw(const class Renderer& render) const;

        const Transform& GetTransform() const;
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        int m_width = 0;
		int m_height = 0;

    };
}