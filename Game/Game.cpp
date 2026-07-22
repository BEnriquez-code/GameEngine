#include "Engine.h"
#include "Player.h"
#include <fmod.hpp>

#include "SDL3/SDL.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace nu;


int main() {
    //Intialization
    Engine::Get().Initialize();


    cout << "Directory Operations:\n";
    cout << "Working directory: " << GetWorkingDirectory() << "\n";
    cout << "Setting directory to 'Assets'...\n";
    SetWorkingDirectory("Assets");
    cout << "New directory: " << GetWorkingDirectory() << "\n\n";

    cout << "Files in Directory:\n";
    auto filenames = GetFilesInDirectory(GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        cout << filename << "\n";
    }
    cout << "\n";

    if (!filenames.empty())
    {
        // get filename
        string str = GetFilename(filenames[0]);
        cout << "Filename: " << str << "\n";

        // get extension
        str = GetFileExtension(filenames[0]);
        cout << "Extension: " << str << "\n";

        // get filename no extension
        str = GetFilenameNoExtension(filenames[0]);
        cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (nu::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }
    
    Engine::Get().GetAudio().AddSound("test", "test.wav");
    Engine::Get().GetAudio().AddSound("thrust", "thrust.wav");
    Engine::Get().GetAudio().AddSound("mario", "mario.mp3");
    Engine::Get().GetAudio().AddSound("hee-hee", "hee-hee.mp3");
    Engine::Get().GetAudio().AddSound("bass", "bass.wav");
    

    Mesh cockpitMesh{ 
        { 
            Vector2{ 2, 0 }, 
            Vector2{ 1, 0.5f }, 
            Vector2{ 1, -0.5f }, 
            Vector2{ 2, 0 }
        }, 
           Color{1.0f, 1.0f, 0.0f} 
    };

    Mesh bodyMesh {
        {
           Vector2{1, 0.5f},
           Vector2{-2, 0.5f},
           Vector2{-2, -0.5f},
		   Vector2{1, -0.5f},
		   Vector2{1, 0.5f},
        },
        Color{0.0f, 1.0f, 1.0f}
    };

    Mesh leftWingMesh {
        {
            Vector2{0, 0.5f},
            Vector2{-1.5f, 2},
            Vector2{-2, 2},
            Vector2{-1.5, 0.5f}
        },
        Color{1.0f, 0.0f, 1.0f}
	};

    Mesh rightWinMesh {
        {
            Vector2{0, -0.5f},
            Vector2{-1.5f, -2},
            Vector2{-2, -2},
            Vector2{-1.5f, -0.5f}
        },
        Color{0.0f, 1.0f, 0.0f}
    };

    Mesh flameMesh{ 
        {
            Vector2{-2, 0.5},
            Vector2{-3, 0.7f},
            Vector2{-2.5f, 0.3f},
            Vector2{-3, 0},
			Vector2{-2.5f, -0.3f},
            Vector2{-3, -0.7f},
			Vector2{-2, -0.5f}
        },
        Color{1.0f, 0.0f, 0.0f}
    };

	Model playerModel{ {cockpitMesh, bodyMesh, leftWingMesh, rightWinMesh, flameMesh} };
	
    Player player{ Transform {Vector2{640.0f, 512.0f}, 0.0f, 50.0f}, playerModel };

    Vector2 position{640.0f, 512.0f};
    Vector2 vel{ 0.0f, 0.0f };

    vector<Vector2> mouseLinePoints;

    Engine::Get().GetAudio().PlaySound("hee-hee");
   
   
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
        
        //player.SetRotation(player.GetTransform().rotation + (90.0f * Engine::Get().GetTime().GetDeltaTime()));
        player.Update(Engine::Get().GetTime().GetDeltaTime());


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
       

		player.Draw(Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().Present();
    }

    Engine::Get().GetRenderer().Shutdown();

    return 0;
}