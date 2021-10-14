#include "Object.h"
#include "ResourcePath.h"

Object::Object()
{
    shape_ = sf::CircleShape(100.0f);
    shape_.setFillColor(sf::Color::Blue);
    shape_.setOrigin(shape_.getRadius() / 2, shape_.getRadius() / 2);
    shape_.setPosition(sf::Vector2f{50, 250});
    offset_ = sf::Vector2f{50, -50};

    if (!shipImage_.loadFromFile(resourcePath() + "Sprites/Ship/Ship.png"))
    {
        throw std::runtime_error("Cannot Load Ship Image");
    }

    ship_.setTexture(shipImage_);
    ship_.setPosition(10, 30);

    shoot_.setFillColor(sf::Color::Yellow);
    shoot_.setString("* Shots Fired! *");

    if (!shootFont_.loadFromFile(resourcePath() + "Fonts/cs.ttf"))
    {
        throw std::runtime_error("Cannot Load Shoot Font");
    }
    shoot_.setFont(shootFont_);
    shoot_.setCharacterSize(5);

    showShoot_ = false;
    shoot_.setPosition(10, 10);
    shootTime_ = 0.0f;
}

Object::~Object()
{
}

void Object::tick(sf::Time time)
{
    auto elapsed = time.asSeconds();
    offset_.y += 10 * elapsed;
    shape_.move(offset_ * elapsed);

    if (showShoot_)
    {

        shootTime_ += elapsed;

        if (shootTime_ > shootTimeOut_)
        {
            showShoot_ = false;
        }
    }
}

void Object::move(Direction direction, sf::Time time)
{
    auto elapsed = time.asSeconds();
    float distance = elapsed * 500;
    switch (direction)
    {
    case Direction::Down:
        shape_.move(sf::Vector2f{0, distance});
        ship_.move(sf::Vector2f{0, distance});
        break;
    case Direction::Up:
        shape_.move(sf::Vector2f{0, -distance});
        ship_.move(sf::Vector2f{0, -distance});
        break;
    case Direction::Left:
        shape_.move(sf::Vector2f{-distance, 0});
        ship_.move(sf::Vector2f{-distance, 0});
        break;
    case Direction::Right:
        shape_.move(sf::Vector2f{distance, 0});
        ship_.move(sf::Vector2f{distance, 0});
        break;
    default:
        //none
        break;
    }
}

void Object::shoot()
{

    const string MESSAGES[] = {"* Shots Fired *",
                               "much WOW",
                               "BAM!",
                               "*pew pew*"};

    if (!showShoot_)
    {
        int index = rand() % 4;

        shoot_.setString(MESSAGES[index]);
        showShoot_ = true;
        shootTime_ = 0.0f;
    }
}

vector<sf::Drawable *> Object::getDrawable()
{
    // return &shape_;
    vector<sf::Drawable *> out;
    out.push_back(&ship_);

    if (showShoot_)
        out.push_back(&shoot_);

    return out;
}