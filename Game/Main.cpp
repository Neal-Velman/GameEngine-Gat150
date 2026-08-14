#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Assets.h"
#include "SpaceGame.h"

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

    nu::Factory::Instance().Register<nu::Actor>("Actor");
    nu::Factory::Instance().Register<nu::Object>("Object");
    nu::Factory::Instance().Register<Player>("Player");
    nu::Factory::Instance().Register<Enemy>("Enemy");
    nu::Factory::Instance().Register<Bullet>("Bullet");
    /*

    auto actor = nu::Factory::Instance().Create<nu::Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;

    auto object = nu::Factory::Instance().Create("Object");
    std::cout << object->IsActive() << std::endl;

    auto player = nu::Factory::Instance().Create<Player>("Player");
    std::cout << player->IsActive() << std::endl;

    


    return 0;
    */

    // INITIALIZATION


    nu::Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    bool quit = false;
    // MAIN LOOP

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
        audio->update();
        float dt = nu::Engine::Get().GetTime().GetDeltaTime();
        game.Update(dt);

        // RENDER
        // Character
        nu::Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::Engine::Get().GetRenderer().Clear();

        
        game.Draw(nu::Engine::Get().GetRenderer());

        nu::Engine::Get().GetPS().Draw(nu::Engine::Get().GetRenderer());
        nu::Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    nu::Engine::Get().Shutdown();
    
    return 0;
}