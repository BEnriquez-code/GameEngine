#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <fmod.hpp>

#include "SDL3/SDL.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace nu;


int main() {
    SetWorkingDirectory("Assets");

    //Intialization
    Engine::Get().Initialize();
    SpaceGame game;
    game.Initialize();

    SetWorkingDirectory("Fonts");
    Font* font = new Font();
    font->Load("Arcade.ttf", 90);

    Text* text = new Text(font);
    text->Create(Engine::Get().GetRenderer(), "Hello World", Vector3{0.0f, 1.0f, 0.0f});

    //SetWorkingDirectory("Assets");
    
    Engine::Get().GetAudio().AddSound("test", "test.wav");
    Engine::Get().GetAudio().AddSound("thrust", "thrust.wav");
    Engine::Get().GetAudio().AddSound("mario", "mario.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("bass", "bass.wav");
    

    Vector2 position{640.0f, 512.0f};
    Vector2 vel{ 0.0f, 0.0f };

    vector<Vector2> mouseLinePoints;   
   
	//MAIN LOOP
    bool quit = false;
    while (!quit) {
		//Update
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                    quit = true;
			}
        }


        Engine::Get().Update();
        
        
        game.Update(Engine::Get().GetTime().GetDeltaTime());

        if (Engine::Get().GetInput().GetButtonDown(Input::MouseButton::Left)) {
			Vector2 v = Engine::Get().GetInput().GetMousePosition();
            if (mouseLinePoints.empty()) {
                mouseLinePoints.push_back(v);
            }
            else{
                float distance = (v - mouseLinePoints.back()).Length();

                if (distance > 10.0f) {
                    mouseLinePoints.push_back(v);
                }
            }
            
		}

        if (Engine::Get().GetInput().GetButtonPressed(Input::MouseButton::Right)) {
            if (!mouseLinePoints.empty())mouseLinePoints.pop_back();
		}

        

        //Render
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i< (int)mouseLinePoints.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            Engine::Get().GetRenderer().DrawLine(mouseLinePoints[i].x, mouseLinePoints[i].y, mouseLinePoints[i+1].x, mouseLinePoints[i+1].y);
        }
       
        text->Draw(Engine::Get().GetRenderer(), 40.0f, 40.0f);


		game.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }
    game.Shutdown();
    Engine::Get().Shutdown();

    return 0;
}