#include "doctest_proxy.h"
#include "../game-source-code/Spider.h"

TEST_SUITE_BEGIN("Spider");

static int spiderIsNotInBounds(Spider &spider)
{
	auto current = spider.getPosition();

	if (current.x > Spider::MAX_X)
	{
		return 1;
	}
	else if (current.x < Spider::MIN_X)
	{
		return 2;
	}
	if (current.y > Spider::MAX_Y)
	{
		return 3;
	}
	else if (current.y < Spider::MIN_Y)
	{
		return 4;
	}

	return 0;
}

TEST_CASE("Test that spider returns to game area when out of bounds")
{
	auto spider = Spider();
	spider.setPosition(224, 150);
	auto dt = sf::Time(sf::seconds(0.1));

	bool goesOutOfBounds = false;
	bool returns = false;

	for (auto i = 1; i <= 200; i++)
	{
		spider.tick(dt);
		auto d = spiderIsNotInBounds(spider);

		if (d && !goesOutOfBounds)
		{
			goesOutOfBounds = true;
		}

		if (!d && goesOutOfBounds)
		{
			returns = true;
			break;
		}
	}

	CHECK(returns);
	CHECK(goesOutOfBounds);
}

TEST_CASE("Spider is destroyed correctly")
{

	GameEntity::entityType type;
	auto spider = Spider();
	SUBCASE("Spider shot by bulled")
	{
		type = GameEntity::entityType::Bullet;
	}
	SUBCASE("Spider is killed by DDT Explosion")
	{
		type = GameEntity::entityType::Explosion;
	}

	// No collisions
	CHECK_FALSE(spider.toDelete());

	auto rect = sf::FloatRect();
	// Touches
	spider.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK(spider.toDelete());
}

TEST_SUITE_END();