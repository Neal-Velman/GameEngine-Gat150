#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <random>
#include <fstream>

class Animal {

public:
    virtual void speak() {
        std::cout << "Animal noises" << std::endl;
    }

};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow" << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof" << std::endl;
    }
};

class Cow : public Animal {
public:
    void speak() override {
        std::cout << "Moo" << std::endl;
    }
};

enum class Type {
    CAT = 1,
    DOG,
    COW
};

Animal* AnimalFactory(const std::string& id) {
    Animal* animal = nullptr;

    if (nu::ToLower(id) == "CAT") animal = new Cat();
    else if (nu::ToUpper(id) == "DOG") animal = new Dog();
    else if (nu::EqualsIgnoreCase(id, "COW")) animal = new Cow();

    return animal;
}

//class ICreator {
//public:
//    virtual ~ICreator() = default;
//    virtual std::unique_ptr<Animal> Create() = 0;
//};
//
//template <typename T>
//class Creator : public ICreator {
//public:
//    std::unique_ptr<Animal> Create() override { return std::make_unique<T>(); }
//};
//
//std::map<std::string, std::unique_ptr<ICreator>> registry;


//enum class Type {
//    CAT = 1,
//    DOG,
//    COW
//};
//
//Animal* AnimalFactory(const std::string& id) {
//    Animal* animal = nullptr;
//    switch (id) {
//    case Type::CAT:
//        animal = new Cat();
//        break;
//    case Type::DOG:
//        animal = new Dog();
//        break;
//    case Type::COW:
//        animal = new Cow();
//        break;
//    default:
//        std::cout << "Invalid selection" << std::endl;
//        break;
//    }
//
//
//    return animal;
//}

int main() {
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!
    nu::SetWorkingDirectory("Assets");
    // KEEP AT DA TOP!!!!!!!!!!!!!!!!!!!!!


    nu::Factory::Instance().Register<nu::Actor>("Actor");
    nu::Factory::Instance().Register<nu::Object>("Object");
    nu::Factory::Instance().Register<Player>("Player");

    auto actor = nu::Factory::Instance().Create<nu::Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;

    auto object = nu::Factory::Instance().Create("Object");
    std::cout << object->IsActive() << std::endl;

    auto player = nu::Factory::Instance().Create<Player>("Player");
    std::cout << player->IsActive() << std::endl;

    nu::json::document_t document;
    if (nu::json::Load("Data/scene.json", document)) {
        player->Read(document);
        std::cout << player->GetName() << std::endl;
        std::cout << player->GetTag() << std::endl;
        std::cout << player->GetTransform().rotation << std::endl;
        std::cout << player->GetSpeed() << std::endl;
    }


    return 0;
    /*registry["CAT"] = std::make_unique<Creator<Cat>>();
    registry["DOG"] = std::make_unique<Creator<Dog>>();
    {
        auto animal = registry["DOG"]->Create();
        animal->speak();
    }*/
    
 //   std::string selection;
 //   std::cout << "Select an animal:" << std::endl;
 //   std::cin >> selection;

	//auto animal = AnimalFactory(selection);
 //   animal->speak();



    // INITIALIZATION

/*    // load the json data from a file
    std::string buffer;
    if (nu::ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (nu::json::Load("data/data.json", document))
        {
            // read/show the data from the json file
            std::string name;
            int age;
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }
        
    }
    */


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