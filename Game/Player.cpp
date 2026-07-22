#include "Player.h"
#include "Renderer.h"
#include "Engine.h"

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

    SetVelocity(GetVelocity() + (force * dt));
    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}