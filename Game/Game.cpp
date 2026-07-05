#include "Engine.h"
#include "SDL3/SDL.h"
#include "Renderer.h"

#include <iostream>
using namespace std;

int main() {
    nu::Renderer render;
    const int windowWidth = 1920;
    const int windowHeight = 1024;

    render.Initialize("Game Engine", windowWidth, windowHeight);

    // handle events
    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    //SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        render.SetColor(0, 0, 0, 0);
        render.Clear();

        //render.SetColor(270, 190, 200, 200);
        //render.DrawFillRect(255, 255, 255, 255);

       

        for (int i = 0; i < 12; i++) {
            float x1 = rand() % windowWidth;
            float y1 = rand() % windowHeight;
            float x2 = rand() % windowWidth;
            float y2 = rand() % windowHeight;

            render.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            render.DrawLine(x1, y1, x2, y2);
        }
               
        for (int i = 0; i < 20; i++) {
            float x = rand() % windowWidth;
            float y = rand() % windowHeight;


            render.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            render.DrawPoint(x, y);
        }

        for (int i = 0; i < 5; i++) {
            float x = rand() % windowWidth;
            float y = rand() % windowHeight;
			float w = rand() % 200 + 50;
			float h = rand() % 200 + 50;


            render.SetColor(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
            render.DrawRect(x, y, w, h);
        }


        render.Present();
    }

    render.Shutdown();

    return 0;
}