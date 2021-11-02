#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest_proxy.h"
#include "../game-source-code/GameWindow.h"
#include "../game-source-code/GameEntity.h"
#include <memory>
#include <iostream>
#include <math.h>
#include "ShipTests.cpp"
#include "BulletTests.cpp"
#include "GameEntityTests.cpp"
#include "CentipedeTests.cpp"
#include "EntityManagerTests.cpp"

TEST_CASE("Testing Window Default Dimensions")
{
	auto window = GameWindow();

	CHECK(window.getSize() == sf::Vector2u{1024, 768});
}
