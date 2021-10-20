#include "doctest.h"
#include "../game-source-code/Ship.h"

TEST_CASE("Ship moves with input")
{
    auto ship = Ship();
    ship.setPosition(sf::Vector2f{120.0f, 200.0f});
    auto dt = sf::Time{sf::seconds(0.016)};
    auto position = ship.getPosition();

    SUBCASE("Ship moves left")
    {
        ship.inputMove(Ship::Direction::Left, dt);
        CHECK(ship.getPosition().x < position.x);
    }
    SUBCASE("Ship moves right")
    {
        ship.inputMove(Ship::Direction::Right, dt);
        CHECK(ship.getPosition().x > position.x);
    }
    SUBCASE("Ship moves up")
    {
        ship.inputMove(Ship::Direction::Up, dt);
        CHECK(ship.getPosition().y < position.y);
    }
    SUBCASE("Ship moves down")
    {
        ship.inputMove(Ship::Direction::Down, dt);
        CHECK(ship.getPosition().y > position.y);
    }
}

TEST_CASE("Ship Stays in bounds")
{
    auto ship = Ship();
    auto dt = sf::Time{sf::seconds(0.016)};

    SUBCASE("Left boundary")
    {
        auto postion = sf::Vector2f{-20.0f, 220.0f};
        ship.setPosition(postion);
        ship.tick(dt);
        CHECK((ship.getPosition().x == ship.MIN_X && ship.getPosition().y == postion.y));
    }
    SUBCASE("Right boundary")
    {
        auto postion = sf::Vector2f{300.0f, 220.0f};
        ship.setPosition(postion);
        ship.tick(dt);
        CHECK((ship.getPosition().x == ship.MAX_X && ship.getPosition().y == postion.y));
    }
    SUBCASE("Upper boundary")
    {
        auto postion = sf::Vector2f{120.0f, 0.0f};
        ship.setPosition(postion);
        ship.tick(dt);
        CHECK((ship.getPosition().x == postion.x && ship.getPosition().y == ship.MIN_Y));
    }
    SUBCASE("Lower boundary")
    {
        auto postion = sf::Vector2f{120.0f, 300.0f};
        ship.setPosition(postion);
        ship.tick(dt);
        CHECK((ship.getPosition().x == postion.x && ship.getPosition().y == ship.MAX_Y));
    }
}

TEST_CASE("Ship can fire bullets")
{
    auto ship = Ship();
    auto dt = sf::Time{sf::seconds(0.016)};

    SUBCASE("Bullet created at ship position")
    {
        CHECK(ship.createQueue_.size() == 0);
        ship.fire();
        CHECK(ship.createQueue_.size() == 1);
        CHECK(ship.createQueue_.back().second == ship.getPosition());
    }

    SUBCASE("Firing is rate limited")
    {
        CHECK(ship.createQueue_.size() == 0);
        ship.fire();
        CHECK(ship.createQueue_.size() == 1);
        ship.fire();
        CHECK(ship.createQueue_.size() == 1);
        ship.tick(dt);
        ship.fire();
        CHECK(ship.createQueue_.size() == 1);
        ship.tick(sf::Time{sf::seconds(0.5)});
        ship.fire();
        CHECK(ship.createQueue_.size() == 2);
    }
}

TEST_CASE("Ship dies correctly")
{
    auto ship = Ship();
    CHECK(ship.getCondition() == Ship::Condition::Alive);
    ship.handleCollision(GameEntity::entityType::CentipedeSegment, sf::FloatRect{0.f, 0.f, 10.f, 10.f});
    SUBCASE("State changes to dying on collision with centipede")
    {
        CHECK(ship.getCondition() == Ship::Condition::Dying);
    }
    SUBCASE("Ship requests removal after dying animation")
    {
        CHECK(!ship.toDelete());
        auto dt = sf::Time{sf::seconds(0.016)};
        while(!ship.animateDone())
        {
            ship.animateTick(dt);
            ship.tick(dt);
        }
        ship.tick(dt);
        CHECK(ship.toDelete());
    }
}