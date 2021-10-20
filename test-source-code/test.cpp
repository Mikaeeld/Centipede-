#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../game-source-code/GameWindow.h"
#include "../game-source-code/GameEntity.h"
#include <memory>
#include <iostream>
#include <math.h>
#include "ShipTests.cpp"
#include "BulletTests.cpp"

TEST_CASE("Testing Window Default Dimensions")
{
	auto window = GameWindow();

	CHECK(window.getSize() == sf::Vector2u{1024, 768});
}

// Test code for Game Entity

// Test the KeyFrame Struct and Percentage Struct
TEST_CASE("Testing Percentage Structure")
{
	Percentage a{0.0f};
	Percentage b{150.0f};
	Percentage c{50.0f};
	Percentage d{70.0f};

	SUBCASE("Default Construction")
	{
		Percentage test{};
		CHECK(test == a);
	}
	SUBCASE("Parameterised Construction")
	{
		Percentage test{0.0f};
		CHECK(test == 0.0f);
		CHECK(test == a);
	}
	SUBCASE("Comparative opperators")
	{
		// Less Than
		CHECK(a < c);
		CHECK_FALSE(c < a);
		CHECK(a < b);
		CHECK(c < d);

		// Greater Than
		CHECK(c > a);
		CHECK_FALSE(a > c);

		// Equal
		Percentage test{70.0f};
		CHECK(b == c);
		CHECK(d == test);

		// Not Equal
		CHECK_NE(b, a);

		// Less Than or Equal
		CHECK_LE(c, b);
		CHECK_LE(a, b);

		// Greater Than or Equal
		CHECK_GE(b, c);
		CHECK_GE(b, a);
	}
	SUBCASE("Addition and Subtraction")
	{
		CHECK((a + b) == 50.0f);
		Percentage test = a - c;
		CHECK(test == Percentage{-50.0f});
		CHECK((d - c) == 20.0f);
	}
}
TEST_CASE("Testing KeyFrame Structure")
{

	shared_ptr<sf::Texture> texture(new sf::Texture);
	KeyFrame a{0.0f, texture};
	KeyFrame b{150.0f, texture};
	KeyFrame c{50.0f, texture};
	KeyFrame d{70.0f, texture};

	SUBCASE("Default Construction")
	{
		KeyFrame test{};
		CHECK(test == a);
	}
	SUBCASE("Parameterised Construction")
	{
		KeyFrame test{0.0f, texture};
		CHECK(test.percent == 0.0f);
		CHECK(test == a);
	}
	SUBCASE("Comparative opperators")
	{
		// Less Than
		CHECK(a < c);
		CHECK_FALSE(c < a);
		CHECK(a < b);
		CHECK(c < d);

		// Greater Than
		CHECK(c > a);
		CHECK_FALSE(a > c);

		// Equal
		KeyFrame test{70.0f, texture};
		CHECK(b == c);
		CHECK(d == test);

		// Not Equal
		CHECK_NE(b, a);

		// Less Than or Equal
		CHECK_LE(c, b);
		CHECK_LE(a, b);

		// Greater Than or Equal
		CHECK_GE(b, c);
		CHECK_GE(b, a);
	}
	SUBCASE("Addition and Subtraction")
	{
		// std::cout << "Testing fmod " << a.percent << " - " << b.percent << " = " << (Percentage)(a.percent - b.percent) << std::endl;
		CHECK((a.percent + b.percent) == 50.0f);
		CHECK((Percentage)(a.percent - b.percent) == -50.0f);
		CHECK((d.percent - c.percent) == 20.0f);
	}
}

TEST_CASE("Testing Default Game Entity")
{
	// Default entity is paused and is done
	auto ge = GameEntity();
	SUBCASE("Animate Mode") { CHECK(ge.getAnimateMode() == AnimateMode::pause); }
	SUBCASE("Animate done") { CHECK(ge.animateDone()); }
	SUBCASE("Period") { CHECK(ge.getPeriod() == 1.0f); }
	SUBCASE("Animate End") { CHECK(ge.getAnimateEnd() == 100.0f); }
	SUBCASE("Animate Start") { CHECK(ge.getAnimateStart() == 0.0f); }
}

// TEST_CASE("Testing Mutators and Accessors")
// {
// }

TEST_CASE("Testing KeyFrame Progression Default/Pause Animate Mode")
{
	shared_ptr<sf::Texture> texture(new sf::Texture);

	KeyFrame k1{0.0f, texture};
	KeyFrame k2{50.0f, texture};
	KeyFrame k3{70.0f, texture};

	auto ge = GameEntity();

	SUBCASE("Exception if Key Frame is requested when none are loaded")
	{
		CHECK_THROWS_AS((*ge.getCurrentKeyFrame()).percent, NoKeyFrames);
	}

	ge.addKeyFrame(k1);

	SUBCASE("Only Key Frame is returned")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
	}

	ge.addKeyFrame(k2);
	ge.addKeyFrame(k3);

	SUBCASE("Inital Key Frame")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
		CHECK_FALSE(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::pause);
	}

	// Progress the animation a little bit
	const int us_in_sec = 1000000;

	const int step_55 = 0.55 * us_in_sec;

	sf::Time dt(sf::microseconds(step_55));

	ge.animateTick(dt);

	SUBCASE("Check That Key Frame has not progressed in paused mode")
	{

		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
	}

	ge.setAnimateStart(55.0f);
	ge.setAnimateMode(AnimateMode::pause);

	SUBCASE("CHECK That Key Frame Has Changed Since Start Changed")
	{
		CHECK(*ge.getCurrentKeyFrame() == k2);
		CHECK_FALSE(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::pause);
	}

	ge.setAnimateStart(75.0f);
	ge.setAnimateMode(AnimateMode::pause);

	SUBCASE("CHECK Last Key Frame is returned")
	{
		CHECK(*ge.getCurrentKeyFrame() == k3);
		CHECK_FALSE(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::pause);
	}
}

TEST_CASE("Testing KeyFrame Progression Loop Animate Mode")
{
	shared_ptr<sf::Texture> texture(new sf::Texture);

	KeyFrame k1{0.0f, texture};
	KeyFrame k2{50.0f, texture};
	KeyFrame k3{70.0f, texture};

	auto ge = GameEntity();

	ge.setPeriod(2.0f);

	SUBCASE("Exception if Key Frame is requested when none are loaded")
	{
		CHECK_THROWS_AS((*ge.getCurrentKeyFrame()).percent, NoKeyFrames);
	}

	ge.addKeyFrame(k1);

	ge.setAnimateMode(AnimateMode::loop);

	SUBCASE("Only Key Frame is returned")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
	}

	ge.addKeyFrame(k2);
	ge.addKeyFrame(k3);

	SUBCASE("Inital Key Frame")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::loop);
	}

	// Progress the animation a little bit
	const int us_in_sec = 1000000;

	const int step_55 = 0.55 * us_in_sec;

	sf::Time dt(sf::microseconds(step_55));

	ge.animateTick(dt);

	SUBCASE("Check That Key Frame has not progressed")
	{

		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 1.1 seconds or 55%

	SUBCASE("CHECK That Key Frame Has Changed")
	{
		CHECK(*ge.getCurrentKeyFrame() == k2);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::loop);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 1.65 seconds or 82%

	SUBCASE("CHECK Last Key Frame is returned")
	{
		CHECK(*ge.getCurrentKeyFrame() == k3);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::loop);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 0.2 seconds or 10%

	SUBCASE("CHECK Loop Back to start")
	{
		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::loop);
	}
}

TEST_CASE("Testing KeyFrame Progression Once Animate Mode")
{
	shared_ptr<sf::Texture> texture(new sf::Texture);

	KeyFrame k1{0.0f, texture};
	KeyFrame k2{50.0f, texture};
	KeyFrame k3{70.0f, texture};

	auto ge = GameEntity();

	ge.setPeriod(2.0f);

	SUBCASE("Exception if Key Frame is requested when none are loaded")
	{
		CHECK_THROWS_AS((*ge.getCurrentKeyFrame()).percent, NoKeyFrames);
	}

	ge.addKeyFrame(k1);
	ge.setAnimateMode(AnimateMode::once);

	SUBCASE("Only Key Frame is returned")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
	}

	ge.addKeyFrame(k2);
	ge.addKeyFrame(k3);

	SUBCASE("Inital Key Frame")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once);
	}

	// Progress the animation a little bit
	const int us_in_sec = 1000000;

	const int step_55 = 0.55 * us_in_sec;

	sf::Time dt(sf::microseconds(step_55));

	ge.animateTick(dt);

	SUBCASE("Check That Key Frame has not progressed")
	{

		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
	}

	// Progress Animation
	ge.animateTick(dt); // Should be 1.1 seconds or 55%

	SUBCASE("CHECK That Key Frame Has Changed")
	{
		CHECK(*ge.getCurrentKeyFrame() == k2);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once);
	}

	// Progress Animation
	ge.animateTick(dt); // Should be 1.65 seconds or 82%

	SUBCASE("CHECK Last Key Frame is returned")
	{
		CHECK(*ge.getCurrentKeyFrame() == k3);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once);
	}

	// Progress Animation
	ge.animateTick(dt); // Should be 0.2 seconds or 10%

	SUBCASE("CHECK animation has stoped and on last frame")
	{
		CHECK(*ge.getCurrentKeyFrame() == k3);
		CHECK_FALSE(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once);
	}

	ge.setAnimateMode(AnimateMode::once);

	SUBCASE("CHECK animation has restarted and on first frame")
	{
		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once);
	}
}

TEST_CASE("Testing KeyFrame Progression Once-restart Animate Mode")
{
	shared_ptr<sf::Texture> texture(new sf::Texture);

	KeyFrame k1{0.0f, texture};
	KeyFrame k2{50.0f, texture};
	KeyFrame k3{70.0f, texture};

	auto ge = GameEntity();
	ge.setPeriod(2.0f);

	SUBCASE("Exception if Key Frame is requested when none are loaded")
	{
		CHECK_THROWS_AS((*ge.getCurrentKeyFrame()).percent, NoKeyFrames);
	}

	ge.addKeyFrame(k1);
	ge.setAnimateMode(AnimateMode::once_restart);

	SUBCASE("Only Key Frame is returned")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
	}

	ge.addKeyFrame(k2);
	ge.addKeyFrame(k3);

	SUBCASE("Inital Key Frame")
	{
		CHECK((*ge.getCurrentKeyFrame()) == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once_restart);
	}

	// Progress the animation a little bit
	const int us_in_sec = 1000000;

	const int step_55 = 0.55 * us_in_sec;

	sf::Time dt(sf::microseconds(step_55));

	ge.animateTick(dt);

	SUBCASE("Check That Key Frame has not progressed")
	{

		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 1.1 seconds or 55%

	SUBCASE("CHECK That Key Frame Has Changed")
	{
		CHECK(*ge.getCurrentKeyFrame() == k2);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once_restart);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 1.65 seconds or 82%

	SUBCASE("CHECK Last Key Frame is returned")
	{
		CHECK(*ge.getCurrentKeyFrame() == k3);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once_restart);
	}

	// Progress Animation Past Halfway
	ge.animateTick(dt); // Should be 0.2 seconds or 10%

	SUBCASE("CHECK animation has stoped and on first frame")
	{
		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK_FALSE(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once_restart);
	}

	ge.setAnimateMode(AnimateMode::once_restart);

	SUBCASE("CHECK animation has restarted and on first frame")
	{
		CHECK(*ge.getCurrentKeyFrame() == k1);
		CHECK(ge.animate());
		CHECK(ge.getAnimateMode() == AnimateMode::once_restart);
	}
}

// TEST_CASE("Testing KeyFrame Progression With Non-standard Start and Stop Points")
// {
// 	shared_ptr<sf::Texture> texture(new sf::Texture);

// 	KeyFrame k1{0.0f, texture};
// 	KeyFrame k2{50.0f, texture};
// 	KeyFrame k3{60.0f, texture};
// 	KeyFrame k4{70.0f, texture};
// 	KeyFrame k5{80.0f, texture};
// 	KeyFrame k6{90.0f, texture};

// 	auto ge = GameEntity();
// 	ge.setPeriod(10.0f);
// 	ge.setAnimateStart(50.0f);
// 	ge.setAnimateEnd(85.0f);

// 	SUBCASE("Exception if Key Frame is requested when none are loaded")
// 	{
// 		CHECK_THROWS_AS((*ge.getCurrentKeyFrame()).percent, NoKeyFrames);
// 	}

// 	ge.addKeyFrame(k1);
// 	ge.setAnimateMode(AnimateMode::loop);

// 	SUBCASE("Only Key Frame is returned")
// 	{
// 		CHECK((*ge.getCurrentKeyFrame()) == k1);
// 	}

// 	ge.addKeyFrame(k2);
// 	ge.addKeyFrame(k3);
// 	ge.addKeyFrame(k4);
// 	ge.addKeyFrame(k5);
// 	ge.addKeyFrame(k6);

// 	SUBCASE("Inital Key Frame")
// 	{
// 		CHECK(ge.animate());
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k3);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k4);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k5);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k6);
// 		CHECK(*ge.getCurrentKeyFrame() == k2);
// 		CHECK(ge.getAnimateMode() == AnimateMode::loop);
// 	}

// 	// Progress the animation a little bit
// 	const int us_in_sec = 1000000;
// 	const int step = us_in_sec;

// 	sf::Time dt(sf::microseconds(step));

// 	ge.animateTick(dt);

// 	SUBCASE("Check That Key Frame has not progressed")
// 	{
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k4);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k5);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k6);
// 		CHECK(*ge.getCurrentKeyFrame() == k3);
// 	}

// 	// Progress Animation
// 	ge.animateTick(dt);

// 	SUBCASE("CHECK That Key Frame Has Changed")
// 	{
// 		CHECK(*ge.getCurrentKeyFrame() == k4);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k3);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k5);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k6);
// 		CHECK(ge.animate());
// 		CHECK(ge.getAnimateMode() == AnimateMode::loop);
// 	}

// 	// Progress Animation
// 	ge.animateTick(dt);

// 	SUBCASE("CHECK Last Key Frame is returned")
// 	{
// 		CHECK(*ge.getCurrentKeyFrame() == k5);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k3);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k4);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k2);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k6);
// 		CHECK(ge.animate());
// 		CHECK(ge.getAnimateMode() == AnimateMode::loop);
// 	}

// 	// Progress Animation
// 	ge.animateTick(dt);

// 	// std::cout << "Check Here" << std::endl;
// 	SUBCASE("CHECK Loop Back to start")
// 	{
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k1);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k3);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k4);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k5);
// 		CHECK_FALSE(*ge.getCurrentKeyFrame() == k6);
// 		CHECK(*ge.getCurrentKeyFrame() == k2);
// 		CHECK(ge.animate());
// 		CHECK(ge.getAnimateMode() == AnimateMode::loop);
// 	}
// }