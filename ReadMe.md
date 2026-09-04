# 2D - Sprite-Based Physics-Enabled Engine

## Engine Description
	
This is a simple engine that is able to render 2D sprites, and applies physics to them. It uses a component-based system to apply seperate components to each actor. Components such as rendering, physics, and animation systems, which allow for easy modification with the serialization from rapidjson. It also comes with a demo of two games, which can easily be switched between by changing the auto game in the Main.cpp between SpriteGame and SpaceGame.

## Game Description

The default sprite games is a simple platformer combat game. The player is able to jump around different platforms and attack enemies with the swing of a sword. The enemies chase the player in an attempt to take them out.

## Core Features

- The player needs to be able to damage enemies and take damage from them. Each actor has a health, so when it dies it is removed from the scene.

- The player is able to jump around the level, using Box2D's ApplyForce in order to do so. 

- The enemies chase the player in an attempt to take them out. The basic enemy will follow on the ground, while the flying one is able to pass through tilemap terrain to get to the player.

## Extra Features

- When the player slays an enemy, it will increase their score by a certain amount. When the player dies, their score is reduced by a certain amount, and they return to their original spawn position, deleting all remaining enenmies from the screen. The score and lives remaining are displayed at the top of the screen.

- When the player hits an enemy, it sends the enemy flying into the air. This works on both the flying enemy and basic enemy.

- Upon losing your last life, the game resets back to the title screen, where it can be restarted from the beginning, resetting score and lives.

- A camera will follow the player, keeping them constanly centered onto the screen. The background moves with the camera, as does the score and lives text, allowing for a constant view of their stats.

- The ability to switch between two different games, SpriteGame and SpaceGame, by changing the "auto game - std::make_unique<[GameName]>();" in the Main.cpp file.

## Building and Running

- To build the engine and demo game, press "Ctrl + Shift + B" while in Visual Studio. Make sure you're set to x64 Debug mode. Any other will likely cause a crash or a failure to build properly.

## Limitations

- The audio system is only able to support one audio file, adding a second one causes them to both not work.

- Sometimes when killing an enemy, a Box2D assertion error occurs, likely due to how Box2D is trying to handle an update on an actor with a nullptr.

- Because of the removal of some "fluff" from the Box2D library, the only build that works is Debug x64.

- Some enemies within the SpriteGame get stuck on the tilemap platforms due to their movment logic.

## External Libraries

This engine uses the following libraries for the following purposes:

- **SDL3 / SDL3 Image**: For rendering sprites, windows, and handling basic input from the user's keyboard and mouse.

- **Box2D**: For physics systems, collision detection, and some parts of the component system.

- **rapidjson**: For serialization, allowing actors to easily derive components to use for their rendering, physics and animations.

## External Assets / Applications

- **Neumont GameDev Library / Collection**: A collection of assets, including the player, flying enemy, and enemy, all use assets from here. 

- **Tiled**: An editor that allows for the creation of tilemaps that easily convert to JSON, which allow for easy integration of complex maps.

- **Pippi**: An editor that allows for the creation of animations, spritesheets, and tile maps, all of which can be converted to JSON for simple and easy integration into the engine.