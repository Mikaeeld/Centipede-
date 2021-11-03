#include "doctest_proxy.h"
#include "../game-source-code/Mushroom.h"

TEST_SUITE_BEGIN("Mushroom");

TEST_CASE("Test mushroom can be destroyed by 4 bullets")
{
	auto type = GameEntity::entityType::Bullet;
	auto mushroom = Mushroom();
	auto dt = sf::Time(sf::seconds(0.1));
	// No collisions
	CHECK_FALSE(mushroom.toDelete());

	auto rect = sf::FloatRect();
	// One hit
	mushroom.tick(dt);
	mushroom.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK_FALSE(mushroom.toDelete());

	// Two hits
	mushroom.tick(dt);
	mushroom.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK_FALSE(mushroom.toDelete());

	// Three hits
	mushroom.tick(dt);
	mushroom.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK_FALSE(mushroom.toDelete());

	// Four hits
	mushroom.tick(dt);
	mushroom.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK(mushroom.toDelete());
}

TEST_CASE("Test that mushroom despawns if touching DDT or Explosion")
{
	GameEntity::entityType type;
	auto mushroom = Mushroom();
	SUBCASE("Mushoom Collides with DDT Cloud")
	{
		type = GameEntity::entityType::Explosion;
	}
	SUBCASE("Mushroom Collides with DDT")
	{
		type = GameEntity::entityType::DDT;
	}

	// No collisions
	CHECK_FALSE(mushroom.toDelete());

	auto rect = sf::FloatRect();
	// Touches
	mushroom.handleCollision(type, rect, shared_ptr<GameEntity>());
	CHECK(mushroom.toDelete());
}

TEST_SUITE_END();