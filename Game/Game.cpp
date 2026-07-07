#include "Engine.h"
#include "SDL3/SDL.h"
#include "Renderer.h"
#include "input.h"

#include <iostream>
#include <vector>
using namespace std;
using namespace nu;


int main() {
    //Intialization
    Renderer render;
    const int windowWidth = 1920;
    const int windowHeight = 1024;

    render.Initialize("Game Engine", windowWidth, windowHeight);
    Input input;
	input.Initialize();

	Vector2 vel{ 0.5f, 0.0f};
    vector<Vector2> v;
 

    for (int i = 0; i < 300; i++) {
      
		v.push_back(Vector2{ RandomFloat(windowWidth), RandomFloat(windowHeight) });
       
	}

   
   
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
		input.Update();

        


        Vector2 mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

        //Render
        render.SetColor(0, 0, 0, 0);
        render.Clear();
       
       
       // Random lines
       /*for (int i = 0; i < 12; i++) {
            float x1 = rand() % windowWidth;
            float y1 = rand() % windowHeight;
            float x2 = rand() % windowWidth;
            float y2 = rand() % windowHeight;

            render.SetColor((float)(RandomInt(256)), (float)(RandomInt(256)), (float)(RandomInt(256)), (float)(RandomInt(256)));
            render.DrawLine(x1, y1, x2, y2);
        }*/

		render.SetColor(1.0f, 1.0f, 1.0f);
		render.DrawFillRect(input.GetMousePosition().x -20 , input.GetMousePosition().y - 20, 40, 40);

		//Random points
       /* for (int i = 0; i < v.size(); i++) {
            float x = rand() % windowWidth;
            float y = rand() % windowHeight;


            render.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            v[i] = v[i] + vel;
            render.DrawPoint(v[i].x, v[i].y);
        }*/

		//Random rectangles
       /* for (int i = 0; i < 5; i++) {
            float x = rand() % windowWidth;
            float y = rand() % windowHeight;
			float w = rand() % 200 + 50;
			float h = rand() % 200 + 50;


            render.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            render.DrawRect(x, y, w, h);
        }*/


        render.Present();
    }

    render.Shutdown();

    return 0;
}