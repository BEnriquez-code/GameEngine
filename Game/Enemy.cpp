#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"

#include <iostream>

void Enemy::Update(float dt) {
	Player* player = m_scene->GetActorByName<Player>("Player");
	if (player) {
		nu::Vector2 direction = player->GetTransform().position - m_transform.position;

		float angle = direction.Angle();
		SetRotation(angle * nu::math::RadToDeg);

		m_transform.rotation = angle * nu::math::RadToDeg;
		nu::Vector2 forward{ 1, 0 };

		forward = forward.Rotate(m_transform.rotation * nu::math::DegToRad);
		AddVelocity(forward * m_speed * dt);
	}
	else {
		float thrust = 0.0f;

		float rotate = 0.0f;

		nu::Vector2 forward{ 1, 0 }; // ->
		nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DegToRad) * thrust;
		AddVelocity(velocity * dt);
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
	if (other->GetTag() == "PlayerBullet") {
		SetDestroyed();
		other->SetDestroyed();
	}
	else if (other->GetName() == "Player") {
		other->SetDestroyed();
	}
}