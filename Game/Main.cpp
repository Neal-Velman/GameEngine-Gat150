#include "Engine.h"
#include "SpaceGame/Player.h"
#include "SpaceGame/Enemy.h"
#include "SpaceGame/Bullet.h"
#include "SpaceGame/Assets.h"
#include "SpaceGame/SpaceGame.h"

#include "SpriteGame/SpriteGame.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>

int main() {
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!
    nu::SetWorkingDirectory("Assets");
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!

    // INITIALIZATION
    nu::Engine::Get().Initialize();

    //SpaceGame game;
    auto game = std::make_unique<SpriteGame>();
    game->Initialize();

    // MAIN LOOP
    bool quit = false;

    // UPDATE
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        // UPDATE ENGINE
        nu::Engine::Get().Update();
        float dt = nu::Engine::Get().GetTime().GetDeltaTime();
        game->Update(dt);

        // RENDER

            // Character
        nu::Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::Engine::Get().GetRenderer().Clear();

            // Game
        game->Draw(nu::Engine::Get().GetRenderer());

            // Particle System
        nu::Engine::Get().GetPS().Draw(nu::Engine::Get().GetRenderer());
        nu::Engine::Get().GetRenderer().Present();
    }
    game.reset();
    // SHUTDOWN
    nu::Engine::Get().Shutdown();
    
    return 0;
}