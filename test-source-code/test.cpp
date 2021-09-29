#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/GameWindow.h"

TEST_CASE("Testing Window Default Dimensions")
{
	auto window = GameWindow();

	CHECK(window.getSize() == sf::Vector2u{1024, 768});
}
