#include "doctest_proxy.h"
#include "../game-source-code/CentipedeSegment.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

TEST_SUITE_BEGIN("Centipede");

// Define How Doctest should print sf::Vector2f when errors occur.
namespace doctest
{
	template <typename T>
	struct StringMaker<sf::Vector2<T>>
	{
		static String convert(const sf::Vector2<T> &vec)
		{
			string out = "[x:" + to_string(vec.x) + ", y:" + to_string(vec.y) + "]";
			return out.c_str();
		}
	};
}

// Test code for Centipede
TEST_CASE("Testing Centipede Head initial movement")
{
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));

	auto initial_position = sf::Vector2f(200, 4);

	head->setPosition(initial_position);

	// Check that the head is a head
	CHECK(head->isHead());

	// Check initial position is consistent
	CHECK(head->getPosition() == initial_position);

	auto dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 10; i++)
	{
		head->tick(dt);
	}

	// Check velocity is left initially
	CHECK(head->getPosition() == sf::Vector2f(190, 4));

	for (int i = 1; i <= 190; i++)
	{
		head->tick(dt);
	}

	// Check that centipede has turned down
	CHECK(head->getPosition() == sf::Vector2f(4, 8));

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 170; i++)
	{
		head->tick(dt);
	}

	// Check that centipede is now moving right
	CHECK(head->getPosition().x > 50);
	CHECK(head->getPosition().y == 12);

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 160; i++)
	{
		head->tick(dt);
	}

	// Check that centipede has bounced off wall and moving left again
	CHECK(head->getPosition().x < 170);
	CHECK(head->getPosition().y == 20);
}

static float manDist(sf::Vector2f a, sf::Vector2f b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

static float SegmentsDiff(shared_ptr<CentipedeSegment> a, shared_ptr<CentipedeSegment> b)
{
	return manDist(a->getPosition(), b->getPosition());
}

TEST_CASE("Testing Centipede With Body Segments Movements")
{
	// Create 3 segment centipede
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	auto dt = sf::Time(sf::seconds(0.1));

	sf::Vector2f expectedHeadPosition;
	sf::Vector2f expectedBody1Position;

	SUBCASE("Moves Left")
	{
		head->setPosition(140, 12);
		expectedHeadPosition = sf::Vector2f{100, 12};
		expectedBody1Position = sf::Vector2f{108, 12};
	}
	SUBCASE("Moves Right")
	{
		head->setPosition(140, 12);
		head->setTargetXDirection(CentipedeMove::XDirection::Right);
		expectedHeadPosition = sf::Vector2f{180, 12};
		expectedBody1Position = sf::Vector2f{172, 12};
	}
	SUBCASE("Turns Down and Right")
	{
		head->setPosition(10, 12);
		expectedHeadPosition = sf::Vector2f{30, 20};
		expectedBody1Position = sf::Vector2f{22, 20};
	}
	SUBCASE("Turns Down and Left")
	{
		head->setPosition(230, 12);
		head->setTargetXDirection(CentipedeMove::XDirection::Right);
		expectedHeadPosition = sf::Vector2f{212, 20};
		expectedBody1Position = sf::Vector2f{220, 20};
	}
	SUBCASE("In Player Area")
	{
		SUBCASE("Turns Up At Bottom")
		{
			SUBCASE("Turns Right")
			{
				head->setPosition(10, 244);
				expectedHeadPosition = sf::Vector2f{30, 236};
				expectedBody1Position = sf::Vector2f{22, 236};
			}
			SUBCASE("Turns Left")
			{
				head->setPosition(230, 244);
				head->setTargetXDirection(CentipedeMove::XDirection::Right);
				expectedHeadPosition = sf::Vector2f{212, 236};
				expectedBody1Position = sf::Vector2f{220, 236};
			}
		}
		SUBCASE("Turns Down At Top")
		{
			SUBCASE("Turns Right")
			{
				head->setPosition(10, 204);
				expectedHeadPosition = sf::Vector2f{30, 212};
				expectedBody1Position = sf::Vector2f{22, 212};
			}
			SUBCASE("Turns Left")
			{
				head->setPosition(230, 204);
				head->setTargetXDirection(CentipedeMove::XDirection::Right);
				expectedHeadPosition = sf::Vector2f{212, 212};
				expectedBody1Position = sf::Vector2f{220, 212};
			}
		}
	}

	// progress with 40 ticks of 0.1 second = 40 pixels movement
	for (int i = 1; i <= 40; i++)
		head->tick(dt);

	// Check Segment Positions
	CHECK(head->getPosition() == expectedHeadPosition);
	CHECK(SegmentsDiff(head, body1) == doctest::Approx(8).epsilon(0.25));
	CHECK(SegmentsDiff(head, body2) == doctest::Approx(16).epsilon(0.25));
	// Check follows correctly
	CHECK(body1->getPosition().x == doctest::Approx(expectedBody1Position.x).epsilon(0.25));
	CHECK(body1->getPosition().y == doctest::Approx(expectedBody1Position.y).epsilon(0.25));
	CHECK(SegmentsDiff(body1, body2) == doctest::Approx(8).epsilon(0.25));
}

TEST_CASE("Centipede Collides With Mushroom and Turns")
{
	// Create 3 segment centipede
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	auto dt = sf::Time(sf::seconds(0.1));

	sf::Vector2f expectedHeadPosition;

	auto rect = sf::FloatRect();
	rect.width = 6;
	rect.height = 6;

	SUBCASE("Centipede Should Move Down")
	{
		head->setTargetYDirection(CentipedeMove::YDirection::Down);
		SUBCASE("Centipede Was Moving left")
		{
			head->setTargetXDirection(CentipedeMove::XDirection::Left);
			expectedHeadPosition = sf::Vector2f{158, 52};
			head->setPosition(160, 44);
		}
		SUBCASE("Centipede Was Moving Right")
		{
			head->setTargetXDirection(CentipedeMove::XDirection::Right);
			expectedHeadPosition = sf::Vector2f{140, 52};
			head->setPosition(136, 44);
		}
	}
	SUBCASE("Centipede Should Move Up (valid while in player area)")
	{
		head->setTargetYDirection(CentipedeMove::YDirection::Up);
		SUBCASE("Centipede Was Moving left")
		{
			head->setTargetXDirection(CentipedeMove::XDirection::Left);
			expectedHeadPosition = sf::Vector2f{158, 212};
			head->setPosition(160, 220);
		}
		SUBCASE("Centipede Was Moving Right")
		{
			head->setTargetXDirection(CentipedeMove::XDirection::Right);
			expectedHeadPosition = sf::Vector2f{140, 212};
			head->setPosition(136, 220);
		}
	}

	for (int i = 1; i <= 10; i++)
	{
		head->tick(dt);
	}

	auto mushroom = make_shared<GameEntity>();

	head->handleCollision(GameEntity::entityType::Mushroom, rect, mushroom);
	// progress with 20 ticks of 0.1 second = 20 pixels movement
	for (int i = 1; i <= 20; i++)
	{
		head->tick(dt);
	}

	// Check Segment Positions
	CHECK(head->getPosition() == expectedHeadPosition);
	CHECK(SegmentsDiff(head, body1) == doctest::Approx(8).epsilon(0.25));
	CHECK(SegmentsDiff(head, body2) == doctest::Approx(16).epsilon(0.25));
	CHECK(SegmentsDiff(body1, body2) == doctest::Approx(8).epsilon(0.25));
}

TEST_CASE("Centipede Collides With a Bullet")
{
	// Create 3 segment centipede
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	head->setPosition(100, 52);

	auto dt = sf::Time(sf::seconds(0.1));

	for (int i = 1; i <= 5; i++)
		head->tick(dt);

	shared_ptr<GameEntity> other;

	// Simulate Shot
	SUBCASE("Head is shot")
	{
		CHECK(head->handleCollision(GameEntity::entityType::Bullet, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(body1->isHead());	 // Centipede Splits
		CHECK(head->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(head->createQueue_.size() == 1);
		auto mushroom_create = head->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(head->getPosition().x / GameGrid::CELL_SIZE), floor(head->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK_FALSE(body2->isHead());
	}
	SUBCASE("Middle Body is shot")
	{
		CHECK(body1->handleCollision(GameEntity::entityType::Bullet, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(body2->isHead());	  // Centipede Splits
		CHECK(body1->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(body1->createQueue_.size() == 1);
		auto mushroom_create = body1->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(body1->getPosition().x / GameGrid::CELL_SIZE), floor(body1->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK(head->isHead());
	}
	SUBCASE("Trailing (tail) Body is shot")
	{
		CHECK(body2->handleCollision(GameEntity::entityType::Bullet, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(head->isHead());	  // Centipede Splits
		CHECK(body2->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(body2->createQueue_.size() == 1);
		auto mushroom_create = body2->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(body2->getPosition().x / GameGrid::CELL_SIZE), floor(body2->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK_FALSE(body1->isHead());
	}
}

TEST_CASE("Centipede Collides With an Explosion")
{
	// Create 3 segment centipede
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	head->setPosition(100, 52);

	auto dt = sf::Time(sf::seconds(0.1));

	for (int i = 1; i <= 5; i++)
		head->tick(dt);

	shared_ptr<GameEntity> other;

	// Simulate Shot
	SUBCASE("Head is shot")
	{
		CHECK(head->handleCollision(GameEntity::entityType::Explosion, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(body1->isHead());	 // Centipede Splits
		CHECK(head->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(head->createQueue_.size() == 1);
		auto mushroom_create = head->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(head->getPosition().x / GameGrid::CELL_SIZE), floor(head->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK_FALSE(body2->isHead());
	}
	SUBCASE("Middle Body is shot")
	{
		CHECK(body1->handleCollision(GameEntity::entityType::Explosion, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(body2->isHead());	  // Centipede Splits
		CHECK(body1->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(body1->createQueue_.size() == 1);
		auto mushroom_create = body1->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(body1->getPosition().x / GameGrid::CELL_SIZE), floor(body1->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK(head->isHead());
	}
	SUBCASE("Trailing (tail) Body is shot")
	{
		CHECK(body2->handleCollision(GameEntity::entityType::Explosion, sf::FloatRect(), other));

		head->tick(dt);
		body1->tick(dt);
		body2->tick(dt);

		CHECK(head->isHead());	  // Centipede Splits
		CHECK(body2->toDelete()); // Segment dissapears

		// 1 Mushroom is spawned in place of segment
		CHECK(body2->createQueue_.size() == 1);
		auto mushroom_create = body2->createQueue_.front();
		auto mushroom_spawn = sf::Vector2f{floor(body2->getPosition().x / GameGrid::CELL_SIZE), floor(body2->getPosition().y / GameGrid::CELL_SIZE)} * GameGrid::CELL_SIZE;
		CHECK(mushroom_create.second == mushroom_spawn);
		CHECK(mushroom_create.first == GameEntity::entityType::Mushroom);

		// Check other segment is correct;
		CHECK_FALSE(body1->isHead());
	}
}

TEST_SUITE_END();