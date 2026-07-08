#include "Engine.h"
#include "SDL3/SDL.h"
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
	Time time;

    Vector2 position{};
	float speed = 200.0f;
    vector<Vector2> points;
    
    uint64_t ticks = SDL_GetTicks();
    uint64_t prevticks = ticks;

   
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
        time.Tick();


        if (input.GetButtonDown(Input::MouseButton::Left)) {
			position = input.GetMousePosition();
            if (points.empty()) {
                points.push_back(position);
            }
            float distance = (position - points.back()).Length();

            if (distance > 10.0f) {
                points.push_back(position);
			}

			points.push_back(input.GetMousePosition());
		}
        Vector2 vel{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) {vel.x = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_D)) {vel.x = +speed;}
        if (input.GetKeyDown(SDL_SCANCODE_W)) {vel.y = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_S)) {vel.y = +speed;}

		position += (vel * time.GetDeltaTime());


        Vector2 mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

        //Render
        render.SetColor(0.0f, 0.0f, 0.0f);
        render.Clear();
       

		//Random points
        for (int i = 0; i < (int)points.size() - 1; i++) {

            render.SetColor(RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat());
            render.DrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }

        render.SetColor(1.0f, 1.0f, 1.0f);
        render.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        render.Present();
    }

    render.Shutdown();

    return 0;
}