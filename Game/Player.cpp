#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"

#include <iostream>

void Player::Update(float dt) {

    
    nu::Vector2 force{ 0.0f, 0.0f };

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4)) nu::Engine::Get().GetAudio().PlaySound("test");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) nu::Engine::Get().GetAudio().PlaySound("mario");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2)) nu::Engine::Get().GetAudio().PlaySound("bass");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3)) nu::Engine::Get().GetAudio().PlaySound("hee-hee");
    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_6)) nu::Engine::Get().GetAudio().PlaySound("thrust");

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) {
        force.x = -m_speed;
        
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) { 
        force.x = +m_speed; 
    }

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) { 
        force.y = -m_speed;
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        force.y = +m_speed; 
    }

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        BulletDesc bulletDesc;
        bulletDesc.name = "Bullet";
        bulletDesc.tag = "PlayerBullet";
        bulletDesc.model = assets::bulletModel;
        bulletDesc.transform = m_transform;
        bulletDesc.speed = 1000.0f;
        bulletDesc.lifespan = 2.0f;

        Bullet* bullet = new Bullet(bulletDesc);
        m_scene->AddActor(bullet);
    }
    

    SetVelocity(GetVelocity() + (force * dt));  
    Actor::Update(dt);

    std::cout << m_destroyed << std::endl;
}

void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}