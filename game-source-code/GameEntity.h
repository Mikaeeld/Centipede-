#pragma once
#include "SFML/Graphics.hpp"
#include <functional>
#include <unordered_set>
#include <queue>
#include <set>
#include <memory>
#include <math.h>

using namespace std;

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

struct KeyFrame
{
	Percentage percent;
	shared_ptr<sf::Texture> texture;

	KeyFrame()
	{
		percent = 0.0f;
	}
	KeyFrame(float p, shared_ptr<sf::Texture> t)
	{
		percent = p;
		texture = t;
	};

	string toString()
	{
		return "{" + to_string(percent) + "}";
	}

	bool operator==(const KeyFrame &rhs) const { return this->percent == rhs.percent; };
	bool operator>(const KeyFrame &rhs) const { return this->percent > rhs.percent; };
	bool operator<(const KeyFrame &rhs) const { return this->percent < rhs.percent; };
	bool operator>=(const KeyFrame &rhs) const { return this->percent >= rhs.percent; };
	bool operator<=(const KeyFrame &rhs) const { return this->percent <= rhs.percent; };
	bool operator!=(const KeyFrame &rhs) const { return this->percent != rhs.percent; };
};

enum class AnimateMode
{
	loop,
	pause,
	once,
	once_restart
};

class InvalidAnimationTimings : std::exception
{
	const char *what() const noexcept
	{
		return "Invalid Animation Timings";
	}
};

class NoKeyFrames : std::exception
{
	const char *what() const noexcept
	{
		return "No Key Frames";
	}
};

class GameEntity : public sf::Sprite
{
public:
	GameEntity();
	GameEntity(float period, float phase);
	~GameEntity() {}

	enum class entityType
	{
		Base,
		Ship,
		Mushroom

	};

	virtual entityType getType()
	{
		return entityType::Base;
	}

	/**
	 * @brief This method is defined when inherited
	 *
	 * Purpose is to allow GameEntity to update variables, physics ect.
	 * @param time
	 */
	virtual void tick(sf::Time time)
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
	 *
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

	const float &getPeriod() const
	{
		return period_;
	}

	const Percentage &getAnimateStart() const
	{
		return animateStart_;
	}

	const Percentage &getAnimateEnd() const
	{
		return animateEnd_;
	}

	/**
	 * @brief Set the Animate Start in percentage
	 *
	 * Valid range 0.0 - 100.0
	 *
	 * @param start
	 */
	void setAnimateStart(const float &start);

	/**
	 * @brief Set the Animate End in percentage
	 *
	 * Valid range 0.0 - 100.0
	 *
	 * @param end
	 */
	void setAnimateEnd(const float &end);

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
	 * @brief Returns true if this object colides with 'other'.
	 *
	 * @param other
	 * @return true
	 * @return false
	 */
	bool collidesWith(GameEntity &other) const;

	/**
	 * @brief Get the Current Key Frame
	 *
	 * @return const KeyFrame
	 */
	const KeyFrame *getCurrentKeyFrame();

	/**
	 * @brief Get the Types of the Game Entity
	 *
	 * @return unordered_set<string>
	 */
	unordered_set<string> getTypes() const
	{
		return types_;
	}

	const AnimateMode &getAnimateMode() const { return animateMode_; }

	void setAnimateMode(AnimateMode mode);
	bool toDelete_ = false;
	queue<pair<entityType, sf::Vector2f>> createQueue_;

protected:
	bool originAtCenter_ = true;

private:
	unordered_set<string> types_;
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