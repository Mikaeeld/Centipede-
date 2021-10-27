#include "doctest.h"
#include "../game-source-code/CentipedeSegment.h"
#include "SFML/Graphics.hpp"
#include <iostream>

// Test code for Centipede

TEST_CASE("Testing Centipede Head initial movement")
{
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));

	auto initial_position = sf::Vector2f(200, 4);

	head->setPosition(initial_position);

	SUBCASE("Check that the head is a head")
	{
		CHECK(head->isHead());
	}

	SUBCASE("Check initial position is consistent")
	{
		CHECK(head->getPosition() == initial_position);
	}

	sf::Time dt(sf::seconds(1));

	head->tick(dt);

	SUBCASE("Check velocity is left initially")
	{
		CHECK(head->getPosition() == sf::Vector2f(190, 4));
	}

	dt = sf::Time(sf::seconds(19));
	head->tick(dt);
	SUBCASE("Check that centipede has turned down")
	{
		CHECK(head->getPosition() == sf::Vector2f(4, 8));
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 170; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede is now moving right")
	{
		CHECK(head->getPosition().x > 50);
		CHECK(head->getPosition().y == 12);
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 160; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede has bounced off wall and moving left again")
	{
		CHECK(head->getPosition().x < 170);
		CHECK(head->getPosition().y == 20);
	}
}

static float manDist(sf::Vector2f a, sf::Vector2f b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

static float SegmentsDiff(shared_ptr<CentipedeSegment> a, shared_ptr<CentipedeSegment> b)
{
	return manDist(a->getPosition(), b->getPosition());
}

static bool testMargin(float value, float test, float margin)
{

	if (abs(value - test) <= abs(margin))
		return true;
	else
		return false;
}

TEST_CASE("Testing Centipede With Body movements")
{
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	auto initial_position = sf::Vector2f(200, 4);

	head->setPosition(initial_position);
	body1->setPosition(initial_position.x + 8, initial_position.y);
	body2->setPosition(initial_position.x + 16, initial_position.y);

	SUBCASE("Check that segments are correct")
	{
		CHECK(head->isHead());
		CHECK_FALSE(body1->isHead());
		CHECK_FALSE(body2->isHead());
	}

	SUBCASE("Check initial position is consistent")
	{
		CHECK(head->getPosition() == initial_position);
	}

	sf::Time dt(sf::seconds(1));

	head->tick(dt);

	SUBCASE("Check velocity is left initially")
	{
		CHECK(head->getPosition() == sf::Vector2f(190, 4));
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(19));
	head->tick(dt);
	SUBCASE("Check that centipede has turned down")
	{

		CHECK(head->getPosition().x < 50);
		CHECK(head->getPosition().y >= 4);
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 170; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede is now moving right")
	{
		CHECK(head->getPosition().x > 50);
		CHECK(head->getPosition().y == 12);
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 160; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede has bounced off wall and moving left again")
	{
		CHECK(head->getPosition().x < 170);
		CHECK(head->getPosition().y == 20);
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}
}

TEST_CASE("Testing Centipede With Body Movements at bottom Moves Back Up")
{
	shared_ptr<float> speed(new float(10.0f));
	shared_ptr<CentipedeSegment> head(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body1(new CentipedeSegment(speed));
	shared_ptr<CentipedeSegment> body2(new CentipedeSegment(speed));

	head->updateChain(nullptr, body1);
	body1->updateChain(head, body2);
	body2->updateChain(body1, nullptr);

	auto initial_position = sf::Vector2f(200, 236);

	head->setPosition(initial_position);
	body1->setPosition(initial_position.x - 8, initial_position.y);
	body2->setPosition(initial_position.x - 16, initial_position.y);

	SUBCASE("Check that segments are correct")
	{
		CHECK(head->isHead());
		CHECK_FALSE(body1->isHead());
		CHECK_FALSE(body2->isHead());
	}

	SUBCASE("Check initial position is consistent")
	{
		CHECK(head->getPosition() == initial_position);
	}

	sf::Time dt(sf::seconds(1));

	head->tick(dt);

	SUBCASE("Check velocity is left initially")
	{
		CHECK(head->getPosition() == sf::Vector2f(190, initial_position.y));
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(19));
	head->tick(dt);
	SUBCASE("Check that centipede has turned down")
	{
		CHECK(head->getPosition() == sf::Vector2f(4, initial_position.y + 4));
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 170; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede is now moving right")
	{
		CHECK(head->getPosition().x > 50);
		CHECK(head->getPosition().y == initial_position.y + 8);
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}

	dt = sf::Time(sf::seconds(0.1));
	for (int i = 1; i <= 160; i++)
	{
		head->tick(dt);
	}

	SUBCASE("Check that centipede has bounced up off wall and moving left again")
	{
		CHECK(head->getPosition().x < 170);
		CHECK(head->getPosition().y == initial_position.y);
		CHECK(testMargin(SegmentsDiff(head, body1), 8, 2));
		CHECK(testMargin(SegmentsDiff(body1, body2), 8, 2));
	}
}
