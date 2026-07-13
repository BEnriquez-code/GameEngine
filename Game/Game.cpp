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
    Actor player{ Transform {Vector2{640.0f, 512.0f}, 0, 50.0f} };

    Vector2 position{640.0f, 512.0f};
    Vector2 vel{ 0.0f, 0.0f };
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
			Vector2 v = input.GetMousePosition();
            if (points.empty()) {
                points.push_back(v);
            }
            float distance = (v - points.back()).Length();

            if (distance > 10.0f) {
                points.push_back(v);
			}

			points.push_back(input.GetMousePosition());
		}

        if (input.GetButtonPressed(Input::MouseButton::Right)) {
            if (!points.empty())points.pop_back();
		}

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) {force.x = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_D)) {force.x = +speed;}
        if (input.GetKeyDown(SDL_SCANCODE_W)) {force.y = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_S)) {force.y = +speed;}

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
		player.Update(time.GetDeltaTime());

	/*	vel += (force * time.GetDeltaTime());
		position += (vel * time.GetDeltaTime());

		position.x = math::Wrap(0.0f, (float)windowWidth, position.x);
        position.y = math::Wrap(0.0f, (float)windowHeight, position.y);*/


        Vector2 mousePos;
		SDL_GetMouseState(&mousePos.x, &mousePos.y);

        //Render
        render.SetColor(0.0f, 0.0f, 0.0f);
        render.Clear();
       

		player.Draw(render);
        /*render.SetColor(1.0f, 1.0f, 1.0f);
        render.DrawFillRect(position.x - 20, position.y - 20, 40, 40);*/

        render.Present();
    }

    render.Shutdown();

    return 0;
}