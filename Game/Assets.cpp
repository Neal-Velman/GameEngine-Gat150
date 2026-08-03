#include "Assets.h"

namespace Assets {

    nu::Mesh playerMesh{ { { 2, 0 }, { -1, 2 }, { -0.5, 1.5 }, { 0, 0 }, {-0.5, -1.5 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.75f, 0.25f, 0.25f } };
    nu::Mesh playerMesh2{ { { 2, 0 }, { -1, 3 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { -1, -3 }, { 2, 0 } }, nu::Color{ 0.25f, 0.5f, 0.25f } };
    nu::Mesh playerMesh3{ { { 2, 0 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.1f, 0.2f, 0.75f } };

	nu::Model playerModel { std::vector<nu::Mesh> { playerMesh, playerMesh2, playerMesh3 } };

    nu::Mesh enemyMesh{ { { 2, 0 }, { -1, 2 }, { -0.5, 1.5 }, { 0, 0 }, {-0.5, -1.5 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.75f, 0.25f, 0.25f } };
    nu::Mesh enemyMesh2{ { { 2, 0 }, { -1, 3 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { -1, -3 }, { 2, 0 } }, nu::Color{ 0.25f, 0.5f, 0.25f } };
    nu::Mesh enemyMesh3{ { { 2, 0 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.1f, 0.2f, 0.75f } };

    nu::Model enemyModel{ std::vector<nu::Mesh> { enemyMesh, enemyMesh2, enemyMesh3 } };

    nu::Mesh bulletMesh{ { nu::Vector2{ -1, -1 }, nu::Vector2{ 1, 0 }, nu::Vector2{ -1, 1 }, nu::Vector2{ -1, -1 } }, nu::Color{ 1.0f, 0.0f, 0.0f } };

    nu::Model bulletModel{ std::vector<nu::Mesh> { bulletMesh } };

    nu::Mesh enemy2Mesh{ { { 2, 0 }, { -1, 2 }, { -0.5, 1.5 }, { 0, 0 }, {-0.5, -1.5 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 1.0f, 1.0f, 0.25f } };
    nu::Mesh enemy2Mesh2{ { { 2, 0 }, { -1, 3 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { -1, -3 }, { 2, 0 } }, nu::Color{ 1.0f, 1.0f, 0.25f } };
    nu::Mesh enemy2Mesh3{ { { 2, 0 }, { -1, 2 }, { 0, 0 }, { -1, -2 }, { 2, 0 } }, nu::Color{ 0.1f, 0.2f, 0.75f } };

    nu::Model enemy2Model{ std::vector<nu::Mesh> { enemy2Mesh, enemy2Mesh2, enemy2Mesh3 } };

}