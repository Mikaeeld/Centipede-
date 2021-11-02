#include "doctest_proxy.h"
#include "../game-source-code/EntityManager.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <deque>

// Tests for Entity Manager

static deque<GameEntity_ptr> generateDummyEntitySet(const int n)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(8, 20);

	auto img = sf::Image();

	deque<GameEntity_ptr> entities;
	for (int i = 0; i < n; i++)
	{
		// Create randomly sized entity
		img.create(distrib(gen), distrib(gen), sf::Color::Red);
		auto texture = shared_ptr<sf::Texture>(new sf::Texture());
		texture->loadFromImage(img);
		auto temp = GameEntity_ptr(new GameEntity());
		temp->addKeyFrame(KeyFrame{0.0, texture});
		temp->animateTick(sf::Time(sf::seconds(1)));
		entities.push_back(temp);
	}
	return entities;
}

TEST_CASE("Testing adding, removing and retrieving entities")
{
	const int num = 5;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	for (auto entity : entities)
	{
		em.addEntity(entity);
	}

	SUBCASE("Test that entities are added.")
	{
		auto getEntities = em.getEntities();
		CHECK(em.getCount(GameEntity::entityType::Base) == num);
		CHECK(getEntities.size() == num);
		// Test if particular entity can be found
		CHECK_FALSE(getEntities.find(entities.front()) == getEntities.end());
	}

	// Remove entity
	auto removed = entities.front();
	entities.pop_front();

	em.removeEntity(removed);

	SUBCASE("Test that entity is removed")
	{
		auto getEntities = em.getEntities();
		CHECK(em.getCount(GameEntity::entityType::Base) == num - 1);
		CHECK(getEntities.size() == num - 1);
		CHECK(getEntities.find(removed) == getEntities.end());
	}
}
