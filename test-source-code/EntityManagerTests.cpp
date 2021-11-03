#include "doctest_proxy.h"
#include "../game-source-code/EntityManager.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
#include <deque>

// Tests for Entity Manager

TEST_SUITE_BEGIN("Entity Manager");

// Create a Dummy GameEntity class that has public variables for testing purposes
class DummyEntity : public GameEntity
{
public:
	DummyEntity()
	{
		tickCount_ = 0;
		totalTime_ = 0;
		oneCollisionPerTick_ = false;

		auto texture = shared_ptr<sf::Texture>(new sf::Texture());
		texture->create(8 + (rand() % 12), 8 + (rand() % 12));
		setTexture(*texture);
	}

	void setDynamic(const bool &dynamic)
	{
		dynamic_ = dynamic;
	}

	void setToDelete(const bool &toDelete)
	{
		toDelete_ = toDelete;
	}

	void tick(const sf::Time &time)
	{
		tickCount_++;
		totalTime_ += time.asSeconds();
	}

	bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other) override
	{
		(void)type;
		collisionLog_.push_back(make_tuple(other->getPosition(), other->getTexture()->getSize(), collisionRect));
		return oneCollisionPerTick_;
	}

	std::vector<std::tuple<sf::Vector2f, sf::Vector2u, sf::FloatRect>> collisionLog_;
	string name_;
	float totalTime_;
	int tickCount_;
	bool oneCollisionPerTick_;

private:
};

static deque<shared_ptr<DummyEntity>> generateDummyEntitySet(const int n)
{
	deque<shared_ptr<DummyEntity>> entities;
	for (int i = 0; i < n; i++)
	{
		auto temp = make_shared<DummyEntity>();
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

TEST_CASE("Testing adding using factory")
{
	const int num = 5;
	auto em = EntityManager();

	for (auto i = 1; i <= 5; i++)
		em.addEntity(GameEntity::entityType::Base, sf::Vector2f());

	SUBCASE("Test that entities are added.")
	{
		auto getEntities = em.getEntities();
		CHECK(em.getCount(GameEntity::entityType::Base) == num);
		CHECK(getEntities.size() == num);
	}
}

TEST_CASE("Tick functions are called once for each entity")
{
	const int num = 5;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto &entity : entities)
		em.addEntity(entity);

	em.tick(dt);

	for (auto &entity : entities)
	{
		CHECK(entity->tickCount_ == 1);
		CHECK(entity->totalTime_ == timeStep);
	}

	for (auto i = 1; i <= 5; i++)
		em.tick(dt);

	for (auto &entity : entities)
	{
		CHECK(entity->tickCount_ == 6);
		CHECK(entity->totalTime_ == timeStep * 6);
	}
}

TEST_CASE("Entity That is self-requested to be deleted is deleted")
{
	const int num = 5;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	auto toDeleteEntity = entities.front();

	for (auto &entity : entities)
		em.addEntity(entity);

	em.tick(dt);

	// Ensure that entity exists in manager
	CHECK(em.getCount(GameEntity::entityType::Base) == num);
	CHECK_FALSE(em.getEntities().find(toDeleteEntity) == em.getEntities().end());

	// Request for the entity to be removed
	toDeleteEntity->setToDelete(true);

	em.tick(dt);
	em.tick(dt);

	// Check that entity has been removed
	CHECK(em.getCount(GameEntity::entityType::Base) == num - 1);
	CHECK(em.getEntities().find(toDeleteEntity) == em.getEntities().end());
}

TEST_CASE("Entities that are requested to be added by another entity are added")
{
	const int num = 5;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	auto parent = entities.front();

	for (auto &entity : entities)
		em.addEntity(entity);

	em.tick(dt);

	// Check initial size
	CHECK(em.getCount(GameEntity::entityType::Base) == num);

	parent->createQueue_.push(make_pair(GameEntity::entityType::Base, sf::Vector2f()));
	parent->createQueue_.push(make_pair(GameEntity::entityType::Base, sf::Vector2f()));

	em.tick(dt);

	// Check that entity has been removed
	CHECK(em.getCount(GameEntity::entityType::Base) == num + 2);
}

TEST_CASE("Collisions Between two Dynamic entities are triggered")
{
	srand(time(0));
	const int num = 3;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto entity : entities)
		em.addEntity(entity);

	auto a = entities.at(0);
	auto b = entities.at(1);
	auto c = entities.at(2);

	a->setDynamic(true);
	b->setDynamic(true);
	c->setDynamic(false);

	a->setPosition(100, 100);
	b->setPosition(101, 101);
	c->setPosition(0, 0);

	em.tick(dt);

	sf::FloatRect rect;
	CHECK(a->collidesWith(*b, rect));

	// Check number of logged collisions
	CHECK(a->collisionLog_.size() == 1);
	CHECK(b->collisionLog_.size() == 1);
	CHECK(c->collisionLog_.size() == 0);

	CHECK(std::get<0>(a->collisionLog_[0]) == b->getPosition());
	CHECK(std::get<0>(b->collisionLog_[0]) == a->getPosition());

	CHECK(rect == std::get<2>(a->collisionLog_.front()));
}

TEST_CASE("Collisions Between a Dynamic and non-Dynamic entities are triggered")
{
	srand(time(0));
	const int num = 3;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto entity : entities)
		em.addEntity(entity);

	auto a = entities.at(0);
	auto b = entities.at(1);
	auto c = entities.at(2);

	a->setDynamic(true);
	b->setDynamic(false);
	c->setDynamic(false);

	a->setPosition(100, 100);
	b->setPosition(101, 101);
	c->setPosition(0, 0);

	em.tick(dt);

	sf::FloatRect rect;
	CHECK(a->collidesWith(*b, rect));

	// Check number of logged collisions
	CHECK(a->collisionLog_.size() == 1);
	CHECK(b->collisionLog_.size() == 1);
	CHECK(c->collisionLog_.size() == 0);

	CHECK(std::get<0>(a->collisionLog_[0]) == b->getPosition());
	CHECK(std::get<0>(b->collisionLog_[0]) == a->getPosition());

	CHECK(rect == std::get<2>(a->collisionLog_.front()));
}

TEST_CASE("Collisions Between two non-Dynamic entities are not triggered")
{
	srand(time(0));
	const int num = 3;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto entity : entities)
		em.addEntity(entity);

	auto a = entities.at(0);
	auto b = entities.at(1);
	auto c = entities.at(2);

	a->setDynamic(false);
	b->setDynamic(false);
	c->setDynamic(false);

	a->setPosition(100, 100);
	b->setPosition(101, 101);
	c->setPosition(0, 0);

	em.tick(dt);

	sf::FloatRect rect;
	CHECK(a->collidesWith(*b, rect));

	// Check number of logged collisions
	CHECK(a->collisionLog_.size() == 0);
	CHECK(b->collisionLog_.size() == 0);
	CHECK(c->collisionLog_.size() == 0);
}

TEST_CASE("Collsion Handler that returns true, only triggers once per tick")
{
	srand(time(0));
	const int num = 3;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto entity : entities)
		em.addEntity(entity);

	auto a = entities.at(0);
	auto b = entities.at(1);
	auto c = entities.at(2);

	a->setDynamic(true);
	b->setDynamic(false);
	c->setDynamic(false);

	a->oneCollisionPerTick_ = true;

	a->setPosition(100, 100);
	b->setPosition(101, 101);
	c->setPosition(101, 101);

	em.tick(dt);

	// Check number of logged collisions
	CHECK(a->collisionLog_.size() == 1);
	CHECK(b->collisionLog_.size() + c->collisionLog_.size() == 1);
}

TEST_CASE("Collision Handler that returns false, allows multiple collisions per tick")
{
	srand(time(0));
	const int num = 3;
	auto entities = generateDummyEntitySet(num);
	auto em = EntityManager();

	auto timeStep = 0.1f;
	auto dt = sf::Time(sf::seconds(timeStep));

	for (auto entity : entities)
		em.addEntity(entity);

	auto a = entities.at(0);
	auto b = entities.at(1);
	auto c = entities.at(2);

	a->setDynamic(true);
	b->setDynamic(false);
	c->setDynamic(false);

	a->oneCollisionPerTick_ = false;

	a->setPosition(100, 100);
	b->setPosition(101, 101);
	c->setPosition(101, 101);

	em.tick(dt);

	// Check number of logged collisions
	CHECK(a->collisionLog_.size() == 2);
	CHECK(b->collisionLog_.size() + c->collisionLog_.size() == 2);
}

TEST_SUITE_END();