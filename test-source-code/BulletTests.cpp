#include "doctest_proxy.h"
#include "../game-source-code/Bullet.h"

TEST_SUITE_BEGIN("Bullet");

TEST_CASE("Bullet moves correctly")
{
    auto bullet = Bullet();
    auto position = sf::Vector2f{120.f, 200.f};
    auto dt = sf::Time{sf::seconds(0.016)};
    bullet.setPosition(position);
    bullet.tick(dt);
    CHECK(bullet.getPosition().y < position.y);
}

TEST_CASE("Bullet requests removal when out of bounds")
{
    auto bullet = Bullet();
    auto position = sf::Vector2f{120.f, 200.f};
    auto dt = sf::Time{sf::seconds(0.016)};
    bullet.setPosition(position);
    bullet.tick(dt);
    CHECK(!bullet.toDelete());
    position = sf::Vector2f{120.f, -20.f};
    bullet.setPosition(position);
    bullet.tick(dt);
    CHECK(bullet.toDelete());
}

TEST_CASE("Bullet requests removal on relevant collisions")
{
    auto bullet = Bullet();
    auto rectangle = sf::FloatRect{0.f, 0.f, 10.f, 10.f};
    shared_ptr<GameEntity> other;
    CHECK(!bullet.toDelete());
    SUBCASE("Mushroom")
    {
        bullet.handleCollision(GameEntity::entityType::Mushroom, rectangle, other);
        CHECK(bullet.toDelete());
    }
    SUBCASE("Centipede")
    {
        bullet.handleCollision(GameEntity::entityType::CentipedeSegment, rectangle, other);
        CHECK(bullet.toDelete());
    }
    SUBCASE("DDT")
    {
        bullet.handleCollision(GameEntity::entityType::DDT, rectangle, other);
        CHECK(bullet.toDelete());
    }
    SUBCASE("No collision with Ship")
    {
        bullet.handleCollision(GameEntity::entityType::Ship, rectangle, other);
        CHECK(!bullet.toDelete());
    }
    SUBCASE("No collision with explosion")
    {
        bullet.handleCollision(GameEntity::entityType::Explosion, rectangle, other);
        CHECK(!bullet.toDelete());
    }
}

TEST_SUITE_END();