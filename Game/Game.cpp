#include "Engine.h"
#include "Player.h"

#include "SDL3/SDL.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace nu;


int main() {
    //Intialization 
    engine.Initialize();
    
    Mesh mesh{ 
        { 
            Vector2{ 2, 0 }, 
            Vector2{ -2, 2 }, 
            Vector2{ -1, 0 }, 
            Vector2{ -2, -2 }, 
            Vector2{ 2, 0 }
        }, 
           Color{0.0f, 0.0f, 1.0f} 
};
	
    Player player{ Transform {Vector2{640.0f, 512.0f}, 0.0f, 50.0f}, vector<Mesh>{ mesh } };

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

        engine.Update();
        
        player.SetRotation(90.0f);
        player.Update(engine.GetTime().GetDeltaTime());


        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) {
			Vector2 v = engine.GetInput().GetMousePosition();
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

        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right)) {
            if (!mouseLinePoints.empty())mouseLinePoints.pop_back();
		}

        

        //Render
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (int i = 0; i< (int)mouseLinePoints.size() - 1; i++) {
            engine.GetRenderer().SetColor(1.0f, 1.0f, 1.0f);
            engine.GetRenderer().DrawLine(mouseLinePoints[i].x, mouseLinePoints[i].y, mouseLinePoints[i+1].x, mouseLinePoints[i+1].y);
        }
       

		player.Draw(engine.GetRenderer());
        engine.GetRenderer().Present();
    }

    engine.GetRenderer().Shutdown();

    return 0;
}