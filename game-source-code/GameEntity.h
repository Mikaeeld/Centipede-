#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include <unordered_set>
#include <queue>
#include <set>
#include <memory>
#include <math.h>

using namespace std;

using Texture_ptr = shared_ptr<sf::Texture>;

/**
 * @brief Represents a positive percentage. Is a value between 0 and 100.
 * Values that exceed 100 wrap around.
 */
struct Percentage
{
public:
	Percentage(float value)
	{
		this->value = value > 100.0f ? fmod(value, 100.0f) : value;
	}

	Percentage()
	{
		value = 0.0f;
	}

	Percentage &operator=(float rhs)
	{
		value = rhs > 100.0f ? fmod(rhs, 100.0f) : rhs;
		return *this;
	};
	Percentage &operator=(Percentage &rhs)
	{
		value = rhs.value > 100.0f ? fmod(rhs.value, 100.0f) : rhs.value;
		return *this;
	};

	Percentage operator+(Percentage &rhs) const
	{
		return value + rhs.value;
	};

	Percentage operator-(Percentage &rhs) const
	{
		return value - rhs.value;
	};

	operator float() const { return value; };
	bool operator==(const Percentage &rhs) const { return value == rhs.value; };
	bool operator>(const Percentage &rhs) const { return value > rhs.value; };
	bool operator<(const Percentage &rhs) const { return value < rhs.value; };
	bool operator<=(const Percentage &rhs) const { return value <= rhs.value; };
	bool operator>=(const Percentage &rhs) const { return value >= rhs.value; };
	bool operator!=(const Percentage &rhs) const { return value != rhs.value; };

	bool operator==(const float &rhs) const { return value == rhs; };
	bool operator>(const float &rhs) const { return value > rhs; };
	bool operator<(const float &rhs) const { return value < rhs; };
	bool operator<=(const float &rhs) const { return value <= rhs; };
	bool operator>=(const float &rhs) const { return value >= rhs; };
	bool operator!=(const float &rhs) const { return value != rhs; };

	string toString()
	{
		return to_string(value);
	}

private:
	float value;
};

/**
 * @brief A container for allocating a Percentage to a Texture.
 *
 *  Multiple Key Frames are used to form an 'animation'.
 */
struct KeyFrame
{

	Percentage percent;				 /**< Key Frame's Percent */
	shared_ptr<sf::Texture> texture; /**< Key Frame's Texture */

	/**
	 * @brief Construct a new Key Frame object
	 *
	 */
	KeyFrame()
	{
		percent = 0.0f;
	}

	/**
	 * @brief Construct a new Key Frame object
	 *
	 * @param p Percentage
	 * @param t Texture
	 */
	KeyFrame(float p, shared_ptr<sf::Texture> t)
	{
		percent = p;
		texture = t;
	};

	bool operator==(const KeyFrame &rhs) const { return this->percent == rhs.percent; };
	bool operator>(const KeyFrame &rhs) const { return this->percent > rhs.percent; };
	bool operator<(const KeyFrame &rhs) const { return this->percent < rhs.percent; };
	bool operator>=(const KeyFrame &rhs) const { return this->percent >= rhs.percent; };
	bool operator<=(const KeyFrame &rhs) const { return this->percent <= rhs.percent; };
	bool operator!=(const KeyFrame &rhs) const { return this->percent != rhs.percent; };
};

/**
 * @brief A list of all possible animation modes supported by the GameEntity class
 *
 */
enum class AnimateMode
{
	loop,
	pause,
	once,
	once_restart
};

/**
 * @brief This Exception is thrown when Start >= End
 *
 */
class InvalidAnimationTimings : std::exception
{
	const char *what() const noexcept
	{
		return "Invalid Animation Timings";
	}
};

/**
 * @brief This Exception is thrown when a KeyFrame is requested from a GameEntity without any.
 *
 */
class NoKeyFrames : std::exception
{
	const char *what() const noexcept
	{
		return "No Key Frames";
	}
};

/**
 * @brief Base class for all game entities.
 *
 * This class Inherits from SFML's Sprite Class.
 * It is designed to work with an Entity Manager or Stand-alone.
 */
class GameEntity : public sf::Sprite
{
public:
	/**
	 * @brief Construct a new GameEntity object
	 *
	 */
	GameEntity();

	/**
	 * @brief Destroy the GameEntity object
	 *
	 */
	~GameEntity() {}

	/**
	 * @brief A list of all intended derived Enitites
	 *
	 */
	enum class entityType
	{
		Base,
		Ship,
		Mushroom,
		Spider,
		Bullet,
		DDT,
		Explosion,
		CentipedeSegment
	};

	/**
	 * @brief Get the Type of the GameEntity
	 *
	 * @return entityType
	 */
	virtual entityType getType()
	{
		return entityType::Base;
	}

	/**
	 * @brief This method is defined when inherited
	 *
	 * Purpose is to allow GameEntity to update variables, movement, physics ect.
	 * @param time
	 */
	virtual void tick(const sf::Time &time)
	{ /* default */
		totalTime_ += time.asSeconds();
	}

	/**
	 * @brief Changes the texture of the GameEntity to the relevant one.
	 *
	 * @param time
	 */
	void animateTick(sf::Time time);

	/**
	 * @brief Get the Key Frames object
	 *
	 * @return vector<KeyFrame>
	 */
	set<KeyFrame> getKeyFrames() { return keyFrames_; }

	/**
	 * @brief Returns true if key frames should be updated else renders current keyframe.
	 *
	 * @return true
	 * @return false
	 */
	bool animate() const { return animate_; };

	/**
	 * @brief Adds a Key Frame to the Key Frames object
	 *
	 *  Note this performs a sort on the Key Frames object, hence it should be called when creating the object.
	 * @param kf
	 */
	void addKeyFrame(const KeyFrame &kf) { keyFrames_.insert(kf); }

	/**
	 * @brief Removes any Key Frames matching the input.
	 *
	 * @param kf
	 */
	void removeKeyFrame(const float &percent);

	/**
	 * @brief Sets the animation Period in seconds
	 *
	 * @param p
	 */
	void setPeriod(const float &p);

	/**
	 * @brief Get the animation Period in seconds
	 *
	 * @return const float&
	 */
	const float &getPeriod() const
	{
		return period_;
	}

	/**
	 * @brief Get the Percentage at which the animation starts
	 *
	 * @return const Percentage&
	 */
	const Percentage &getAnimateStart() const
	{
		return animateStart_;
	}

	/**
	 * @brief  Get the Percentage at which the animation ends
	 *
	 * @return const Percentage&
	 */
	const Percentage &getAnimateEnd() const
	{
		return animateEnd_;
	}

	/**
	 * @brief Set the Animate Start in percentage
	 *
	 * Throws an exception if invalid.
	 * Valid range 0.0 - 100.0
	 * @param start
	 */
	void setAnimateStart(const float &start);

	/**
	 * @brief Set the Animate End in percentage
	 *
	 * Throws an exception if invalid.
	 * Valid range 0.0 - 100.0
	 * @param end
	 */
	void setAnimateEnd(const float &end);

	/**
	 * @brief Set the animation Start and End Percentages
	 *
	 * @param start
	 * @param end
	 */
	void setAnimateTimings(const float &start, const float &end);

	/**
	 * @brief Returns true if the animation has completed its key frame sequence.
	 *
	 * @return true
	 * @return false
	 */
	bool animateDone() const
	{
		return !animate_;
	}

	/**
	 * @brief A check for collision (intersection) with another GameEntity.
	 *
	 * Writes the intersection geometry to the rect parameter
	 * @param other The other entity.
	 * @param rect  The rectangle to write the intersection geometry.
	 * @return true
	 * @return false
	 */
	bool collidesWith(const GameEntity &other, sf::FloatRect &rect) const;

	/**
	 * @brief This method is defined when inherited.
	 *
	 * This method should be called when it is observed that the GameEntity has collided with another.
	 * Returns true if the GameEntity expects no further collisions for the current tick.
	 * @param type The type of the other entity
	 * @param collisionRect The resulting intersection geometry of the collision
	 * @param other A shared pointer to the other entity
	 * @return true
	 * @return false
	 */
	virtual bool handleCollision(entityType type, sf::FloatRect collisionRect, const shared_ptr<GameEntity> other)
	{
		(void)other;
		(void)type;
		(void)collisionRect;
		return false;
	}

	/**
	 * @brief Get the Current Key Frame
	 *
	 * @return const KeyFrame
	 */
	const KeyFrame *getCurrentKeyFrame();

	/**
	 * @brief Get the Animate Mode object
	 *
	 * @return const AnimateMode&
	 */
	const AnimateMode &getAnimateMode() const { return animateMode_; }

	/**
	 * @brief Set the Animate Mode object
	 *
	 * @param mode
	 */
	void setAnimateMode(AnimateMode mode);

	/**
	 * @brief Returns True if the GameEntity's origin should be at it's centroid
	 *
	 * @return true
	 * @return false
	 */
	const bool &originAtCenter() const
	{
		return originAtCenter_;
	}

	/**
	 * @brief Returns true if the GameEntity requests to be deleted.
	 *
	 * @return true
	 * @return false
	 */
	const bool &toDelete() const { return toDelete_; }

	/**
	 * @brief Returns true if the GameEntity is Dynamic.
	 *
	 * A 'Dynamic' GameEntity is said to move on it's own accords.
	 * @return true
	 * @return false
	 */
	const bool &isDynamic() const { return dynamic_; }

	/**
	 * @brief Stores a queue of Game Entities that this entity requests be created.
	 *
	 */
	queue<pair<entityType, sf::Vector2f>> createQueue_;

protected:
	/**
	 * @brief Stores whether the GameEntity should be centered at its origin
	 *
	 * Set to true by default.
	 */
	bool originAtCenter_ = true;

	/**
	 * @brief  Stores whether the GameEntity should be deleted
	 *
	 * Set to false by default.
	 */
	bool toDelete_ = false;

	/**
	 * @brief Stores whether the GameEntity is Dynamic
	 *
	 * Set to false by default
	 */
	bool dynamic_ = false;

private:
	bool animate_;
	set<KeyFrame> keyFrames_;
	float period_;
	Percentage animateStart_;
	Percentage animateEnd_;
	float currentTime_;
	AnimateMode animateMode_;
	set<KeyFrame>::iterator itr_;
	float totalTime_;
	set<KeyFrame>::iterator getKeyFrameAtPercent(const float &percent);
	void updateKeyFrame();
	void validateStartStopContraints();
};