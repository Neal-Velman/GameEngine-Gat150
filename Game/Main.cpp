#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <map>
#include <memory>

class Object {

public:
    Object() { std::cout << "Constructor" << std::endl; }
    ~Object() { std::cout << "Destructor" << std::endl; }

    Object(const Object& object) { std::cout << "Copy" << std::endl; }
    Object& operator = (const Object& object) { std::cout << "Assignment" << std::endl; return *this; }

};


int main() {

    std::cout << "---------- Object ----------" << std::endl;
    {
        Object objectA;
        Object objectB(objectA);
        Object objectC;
        objectC = objectA;
    }

    std::cout << "---------- Raw Pointers ----------" << std::endl;
    {
        Object* objectA = new Object();
        std::cout << objectA << std::endl;
        Object* objectB = new Object(*objectA);
        std::cout << objectB << std::endl;
        Object* objectC = nullptr;
        objectC = objectA;
        std::cout << objectC << std::endl;


		delete objectA;
		delete objectB;
		//delete objectC;
    }

    std::cout << "---------- Smart Pointers ----------" << std::endl;
    {
        std::unique_ptr<Object> objectA = std::make_unique<Object>();
        std::cout << objectA.get() << std::endl;
        std::unique_ptr<Object> objectB;
        objectB = std::move(objectA);
        std::cout << objectB.get() << std::endl;

        objectB.reset();

    }

    //return 0;

    // INITIALIZATION
    nu::SetWorkingDirectory("Assets");

    nu::Engine::Get().Initialize();

    SpaceGame game;
    game.Initialize();

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    std::vector<nu::Vector2> points;
    /*std::vector<FMOD::Sound*> sounds;*/

    //FMOD::Sound* sound = nullptr;
    //audio->createSound("Audio/test.wav", FMOD_DEFAULT, 0, &sound);
    ////audio->playSound(sound, 0, false, nullptr);

    //FMOD::Sound* sound2 = nullptr;
    //audio->createSound("Audio/bass.wav", FMOD_DEFAULT, 0, &sound2);
    //sounds.push_back(sound2);

    //FMOD::Sound* sound3 = nullptr;
    //audio->createSound("Audio/cowbell.wav", FMOD_DEFAULT, 0, &sound3);
    //sounds.push_back(sound3);

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



        /*if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }*/

        /*if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2)) {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }*/

        if (nu::Engine::Get().GetInput().GetMouseDown(nu::Input::MouseButton::LEFT)) {
            if (points.empty()) {
                points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
            }
            else {
                nu::Vector2 v = points.back() - nu::Engine::Get().GetInput().GetMousePosition();
                if (v.Length() > 10.0f) {
                    points.push_back(nu::Engine::Get().GetInput().GetMousePosition());
                }
            }

        }

        if (nu::Engine::Get().GetInput().GetButtonPressed(nu::Input::MouseButton::RIGHT)) {
            if (!points.empty()) {
                points.pop_back();
            }
        }
        

        // RENDER
        nu::Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        nu::Engine::Get().GetRenderer().Clear();


        for (int i = 0; i < (int)points.size() - 1; i++) {
            nu::Engine::Get().GetRenderer().SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            nu::Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i+1].y);
            nu::Engine::Get().GetRenderer().DrawFillRect(points[i].x, points[i].y, 10, 10);
        }

        // Character
        game.Draw(nu::Engine::Get().GetRenderer());
        nu::Engine::Get().GetPS().Draw(nu::Engine::Get().GetRenderer());
        nu::Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    nu::Engine::Get().Shutdown();
    
    return 0;
}