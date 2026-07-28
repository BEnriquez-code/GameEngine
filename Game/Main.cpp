#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"

#include <fmod.hpp>

#include "SDL3/SDL.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;
using namespace nu;


int main() {
    SetWorkingDirectory("Assets");
    map<string, int> students;
    students["Aiden"] = 16;
    students["Jack"] = 17;
    students["River"] = 15;

    cout << students["Aiden"] << endl;



    //Intialization
    Engine::Get().Initialize();

    Scene scene;

    
    Engine::Get().GetAudio().AddSound("test", "test.wav");
    Engine::Get().GetAudio().AddSound("thrust", "thrust.wav");
    Engine::Get().GetAudio().AddSound("mario", "mario.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("bass", "bass.wav");
    

   

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.tag = "Enemy";
        enemyDesc.model = assets::enemyModel;
        enemyDesc.transform = Transform{ Vector2{RandomFloat((float)Engine::Get().GetRenderer().GetWidth()), RandomFloat((float)Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.damping = 3.0f;
        enemyDesc.speed = RandomFloat(1000.0f, 1500.0f);

        Enemy* enemy = new Enemy(enemyDesc);
        scene.AddActor(enemy);
    }

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
        
        
        scene.Update(Engine::Get().GetTime().GetDeltaTime());

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
       

		scene.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().Shutdown();

    return 0;
}