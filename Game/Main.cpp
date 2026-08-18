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

//class Example {
//public:
//    Example() = default;
//    Example(int* i) : i{ i } {}
//    ~Example() = default;
//
//    Example(const Example& other) {
//        std::cout << "copy constructor" << std::endl;
//        i = other.i;
//    }
//public:
//    int i*{ nullptr };
//};

int main() {
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!
    nu::SetWorkingDirectory("Assets");
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!

    //int* ptr = new int(5);

    //Example example1{ ptr };
    //Example example2{ example1 };

    //std::cout << example1.i << std::endl;
    //std::cout << example2.i << std::endl;

    //return 0;

    /*nu::Factory::Instance().Register<nu::Actor>("Actor");
    nu::Factory::Instance().Register<nu::Object>("Object");
    nu::Factory::Instance().Register<Player>("Player");
    nu::Factory::Instance().Register<Enemy>("Enemy");
    nu::Factory::Instance().Register<Bullet>("Bullet");*/

    // INITIALIZATION
    nu::Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);
    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

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