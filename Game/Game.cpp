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
    
    Mesh mesh{ {Vector2{-3, 3}, Vector2{3,3}, Vector2{0,0} }, Color{0.0f, 0.0f, 1.0f} };

    Actor player{ Transform {Vector2{640.0f, 512.0f}, 0.0f, 50.0f}, vector<Mesh>{ mesh } };

    Vector2 position{640.0f, 512.0f};
    Vector2 vel{ 0.0f, 0.0f };
	float speed = 200.0f;

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
		input.Update();
        time.Tick();


        if (input.GetButtonDown(Input::MouseButton::Left)) {
			Vector2 v = input.GetMousePosition();
            if (mouseLinePoints.empty()) {
                mouseLinePoints.push_back(v);
            }
            else{
                float distance = (v - mouseLinePoints.back()).Length();

                if (distance > 10.0f) {
                    mouseLinePoints.push_back(v);
                }
            }
            

            mouseLinePoints.push_back(input.GetMousePosition());
		}

        if (input.GetButtonPressed(Input::MouseButton::Right)) {
            if (!mouseLinePoints.empty())mouseLinePoints.pop_back();
		}

        Vector2 force{ 0.0f, 0.0f };
        

        if (input.GetKeyDown(SDL_SCANCODE_A)) {force.x = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_D)) {force.x = +speed;}
        if (input.GetKeyDown(SDL_SCANCODE_W)) {force.y = -speed;}
        if (input.GetKeyDown(SDL_SCANCODE_S)) {force.y = +speed;}

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
		player.Update(time.GetDeltaTime());



        //Render
        render.SetColor(0.0f, 0.0f, 0.0f);
        render.Clear();

        for (int i = 0; i< (int)mouseLinePoints.size() - 1; i++) {
            render.SetColor(1.0f, 1.0f, 1.0f);
            render.DrawLine(mouseLinePoints[i].x, mouseLinePoints[i].y, mouseLinePoints[i+1].x, mouseLinePoints[i+1].y);
        }
       

		player.Draw(render);
        render.Present();
    }

    render.Shutdown();

    return 0;
}