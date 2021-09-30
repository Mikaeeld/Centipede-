#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/GameWindow.h"
#include "../game-source-code/GameEntity.h"
#include <memory>

TEST_CASE("Testing Window Default Dimensions")
{
	auto window = GameWindow();

	CHECK(window.getSize() == sf::Vector2u{1024, 768});
}

// Test code for Game Entity

TEST_CASE("Testing Default Game Entity")
{
	// Default entity is paused and is done
	auto ge = GameEntity();
	SUBCASE("Animate Mode") { CHECK(ge.getAnimateMode() == AnimateMode::pause); }
	SUBCASE("Animate done") { CHECK(ge.animateDone()); }
	SUBCASE("Period") { CHECK(ge.getPeriod() == 1.0f); }
	SUBCASE("Animate End") { CHECK(ge.getAnimateEnd() == 1.0f); }
	SUBCASE("Animate Start") { CHECK(ge.getAnimateStart() == 0.0f); }
}

// TEST_CASE("Testing Mutators and Accessors")
// {
// }

// TEST_CASE("Testing KeyFrame Progression Default/Pause Animate Mode")
// {
// 	shared_ptr<sf::Texture> texture(new sf::Texture);

// 	KeyFrame k1{0.0f, texture};
// 	KeyFrame k2{50.0f, texture};
// 	KeyFrame k3{70.0f, texture};

// 	auto ge = GameEntity();
// 	ge.addKeyFrame(k1);
// 	ge.addKeyFrame(k2);
// 	ge.addKeyFrame(k3);

// 	SUBCASE("Inital Key Frame")
// 	{
// 		CHECK(ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(ge.animate());
// 	}

// 	// Progress the animation a little bit

// 	const int us_in_sec = 1000000;

// 	const int step_55 = 0.55 * us_in_sec;

// 	sf::Time dt(sf::microseconds(step_55));

// 	ge.animateTick(dt);

// 	SUBCASE("Check false keyframe progression mode")
// 	{
// 		CHECK(ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(ge.getCurrentKeyFrame() == k2);
// 	}
// }

// TEST_CASE("Testing KeyFrame Progression Loop Animate Mode")
// {
// }

// TEST_CASE("Testing KeyFrame Progression Once Animate Mode")
// {
// }

// TEST_CASE("Testing KeyFrame Progression Once-restart Animate Mode")
// {
// }