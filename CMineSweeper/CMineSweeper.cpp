#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Globals.h"
#include "Window.h"
#include "UI.h"
#include "Component.h"
using namespace std;

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    #ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLErrors("SDL_Init");
    #endif

    IMG_Init(IMG_INIT_PNG);
    #ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLErrors("IMG_Init");
    #endif

    TTF_Init();
    #ifdef SHOW_DEBUG_HELPERS
        Utils::CheckSDLErrors("TTF_Init");
    #endif 

    Engine::Window window;
    MineSweeperUI UI;

    SDL_Event event;
    bool shouldQuit = false;

    while (!shouldQuit)
    {
        //Handle Input
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                shouldQuit = true;
            }
            else
            {
                UI.HandleEvent(event);
            }
        }

        //Update Objects
        window.Render();
        UI.Render(window.GetSurface());

        //Render Frame
        window.UpdateFrame();
    }

    SDL_Quit();
    return 0;
}